import matplotlib.pyplot as plt
import csv
import random
import os
import math

class gene():
    def __init__(self):
        """
        offspring = [chromosome1, chromosome2, ..., [gene1, nene2,...], c[ g[ fs[feature_slice1_1, [LB, RB, CHANC], ...], [feature_slice2_1, 2_2,...]]] ]
        offspring = [species1, species2, ..., [chromosome1, chromosome2,...], s[ c[ g(fs)[feature_slice1_1, [LB, RB, CHANC], ...], [feature_slice2_1, 2_2,...]]] ]
        
        gene set: [ [chromosome: first feature slices], ... ]
        chromosome: [ ...(<bmin), [bmin, max1], [min2,max2], ..., [minn,bmax], ...(>=bmax) ]
        CHANC = (P(LB<= feature2 value< RB | rarget fail), P(LB<= feature2 value< RB | rarget success))
        """
        self.offspring = [] #species
        self.biome_score = []
        self.survived_biome = [] #better species
        self.survived_score = []
        
        self.n_offspring = 100 #child gene number
        self.n_select = 15 #number of species survived after extinction
        self.n_slice = 10 # max slice in each gene when Cambrian_explosion
        self.n_chromosome = 0
        
        self.proportion = False #when crossover, chromosome has better accuracy pass higher proportion of its chromosomes to its offspring
        self.GAM = False #graduatelly advanced mutation(by probablity)
        
        self.twins_chance = 0 #probablity to create a same offspring multi times
        
    def bayes(self,range,data,feature_id):
        n_total = len(data)
        n_total_true = 0
        n_total_false = 0
        n_feature = len(data[0])
        n_false = 0
        n_true = 0
        for i in data:
            if(i[-1]==1):
                n_total_true+=1
            else:
                n_total_false+=1
            if(range[0]<= i[feature_id] < range[1]):
                if(i[-1] == 0):
                    n_false +=1
                else:
                    n_true+=1
        return (round(n_false/n_total_false,5), round(n_true/n_total_true,5))
    def Cambrian_explosion(self,data, n_offspring = -1):
        """
        first mass generate slices by input data total randomly(number base on n_offspring)
        """
        
        #load data
        data_load = data[1]
        feature_range = data[0]
        n_feature = len(data[0])-1
        self.n_chromosome = n_feature
        
        #slice bound(左閉右開)
        lbound = 0
        rbound = 0
        sbound = 0.0 #random slice right bound
        n_slice = 0 #max slice num(base on self.n_slice)
        
        
        n_offspring = n_offspring if n_offspring > 0 else self.n_offspring
        for i in range(n_offspring):
            #total generate
            pass
            temp_species = []
            for j in range(n_feature):
                #every feature slice in each gene
                pass
                n_slice = random.randint(0,self.n_slice)
                lbound = feature_range[j][0]
                rbound = feature_range[j][1]
                
                temp_chromosome = []
                for k in range(n_slice):
                    sbound = round(random.uniform(lbound, rbound),4)
                    
                    temp_chromosome.append([lbound,sbound, self.bayes((lbound,sbound), data_load, j)])
                    lbound = sbound
                temp_chromosome.append([lbound,rbound+1, self.bayes((lbound,rbound+1), data_load, j)])
                temp_species.append(temp_chromosome)
                
            self.offspring.append(temp_species)
            
    def test_total_chromsome_total_validation(self,data,species_biome = -1):
        # species_biome = self.offspring if species_biome == -1 else species_biome
        if(species_biome==-1):species_biome = self.offspring
        for chromsomes in species_biome:
            self.biome_score.append(test_single_chromsome_total_validation(chromsomes,data))          
    def Darwin_time(self,data):
        """
        validates the offspring genes and comes mass extinction, only top genes will survived(number base on n_select)
        """
        #先代加入子代，重新競爭
        
        self.biome_score.clear()
        self.survived_score.clear()
        for seed in self.survived_biome:
            self.offspring.append(seed)
        self.survived_biome.clear()
        self.test_total_chromsome_total_validation(data)
        
        
        for i in range(self.n_select):
            winner = max(self.biome_score)
            self.survived_biome.append(self.offspring[self.biome_score.index(winner)])
            self.survived_score.append(winner)
            self.offspring.remove(self.offspring[self.biome_score.index(winner)])
            self.biome_score.remove(winner)
        self.offspring.clear()
        
        
    def Crossover(self):
        """
        randomly select two or more genes to exchange genes, add these genes to offspring
        continue until the number of offspring reach n_offspring
        """
        def synapsis():
            """
            homologous chromosome change their gene
            """
            pass
        n_survived = len(self.survived_biome)
        for i in range(self.n_offspring):
            male = 1
            female = 0
            while(male != female):
                male = random.randint(0,n_survived-1)
                female = random.randint(0,n_survived-1)
            if(self.proportion):
                male_dominate_gene = self.biome_score[male]/(self.biome_score[male]+self.biome_score[female])
                # female_dominate_gene = self.biome_score[female]/(self.biome_score[male]+self.biome_score[female])
            else:
                male_dominate_gene = 0.5
                # female_dominate_gene = 0.5
            
            new_species = [] #contains chromosome
            for j in range(self.n_chromosome):
                if(random.random()<male_dominate_gene):
                    new_species.append(self.survived_biome[male][j].copy())
                else:
                    new_species.append(self.survived_biome[female][j].copy())
            
            chance = 1
            while(random.random()<chance):
                self.offspring.append(new_species)
                chance = self.twins_chance
        return
        
    def mutation(self,data):
        """
        offspring have a chance to mutation: 
        1. shift: slice may shift
        2. extend: slice may extend while others shorten
        3. merge: slice may merge
        4. split: slice may split part
        5. rebuilt: a whole chromsome may be erased and create a new one
        6. infect: a whole chromsome may be infect by other offspring's chromsome
        7. cheat: a whole chromsome may be inherited form other dominate species instead of their parents 
        8. loss: part of chromsome (a.k.a slice or gene) may disappear
        
        the chance will base on the accuracy of genes, the higher the accuracy is, the lower the chance of mutation will be
        (if the GAM is on)
        """
        def extend_mutate():
            while(round(random.random(),4)<extending_chance):
                id_chromosome = random.randint(0,len(species)-1)
                if(len(species[id_chromosome])<=1):return
                type_extend = random.randint(0,2) if len(species[id_chromosome])>=3 else random.randint(0,1)#0 left, 1 right, 2 both
                if(type_extend==0):
                    id_gene = random.randint(1,len(species[id_chromosome])-1)
                    percentageL = round(random.uniform(-0.9,0.9),4)
                    realL = abs(species[id_chromosome][id_gene-1][1]-species[id_chromosome][id_gene-1][0])*percentageL
                    
                    species[id_chromosome][id_gene-1] = [species[id_chromosome][id_gene-1][0],
                                                            species[id_chromosome][id_gene-1][1]-realL,
                                                            self.bayes((species[id_chromosome][id_gene-1][0],
                                                            species[id_chromosome][id_gene-1][1]-realL),data[1],id_chromosome)]
                    
                    species[id_chromosome][id_gene] = [species[id_chromosome][id_gene][0]+realL,
                                                            species[id_chromosome][id_gene][1],
                                                            self.bayes((species[id_chromosome][id_gene][0]+realL,
                                                            species[id_chromosome][id_gene][1]),data[1],id_chromosome)]
                    
                elif(type_extend==1):
                    id_gene = random.randint(0,len(species[id_chromosome])-2)
                    percentageR = round(random.uniform(-0.9,0.9),4)
                    realR = abs(species[id_chromosome][id_gene+1][1]-species[id_chromosome][id_gene+1][0])*percentageR
                    
                    species[id_chromosome][id_gene+1] = [species[id_chromosome][id_gene+1][0]-realR,
                                                            species[id_chromosome][id_gene-1][1],
                                                            self.bayes((species[id_chromosome][id_gene+1][0]-realR,
                                                            species[id_chromosome][id_gene+1][1]),data[1],id_chromosome)]
                    
                    species[id_chromosome][id_gene] = [species[id_chromosome][id_gene][0],
                                                            species[id_chromosome][id_gene][1]+realR,
                                                            self.bayes((species[id_chromosome][id_gene][0],
                                                            species[id_chromosome][id_gene][1]+realR),data[1],id_chromosome)]
                else:
                    percentageL = round(random.uniform(-0.9,0.9),4)
                    percentageR = round(random.uniform(-0.9,0.9),4)
                    id_gene = random.randint(1,len(species[id_chromosome])-2)
                    
                    realL = abs(species[id_chromosome][id_gene-1][1]-species[id_chromosome][id_gene-1][0])*percentageL
                    realR = abs(species[id_chromosome][id_gene+1][1]-species[id_chromosome][id_gene+1][0])*percentageR
                    
                    species[id_chromosome][id_gene-1] = [species[id_chromosome][id_gene-1][0],
                                                            species[id_chromosome][id_gene-1][1]-realL,
                                                            self.bayes((species[id_chromosome][id_gene-1][0],
                                                            species[id_chromosome][id_gene-1][1]-realL,),data[1],id_chromosome)]
                    
                    species[id_chromosome][id_gene] = [species[id_chromosome][id_gene][0]+realL,
                                                            species[id_chromosome][id_gene][1],
                                                            self.bayes((species[id_chromosome][id_gene][0]+realL,
                                                            species[id_chromosome][id_gene][1],),data[1],id_chromosome)]
                    
                    species[id_chromosome][id_gene+1] = [species[id_chromosome][id_gene+1][0]-realR,
                                                            species[id_chromosome][id_gene-1][1],
                                                            self.bayes((species[id_chromosome][id_gene+1][0]-realR,
                                                            species[id_chromosome][id_gene+1][1]),data[1],id_chromosome)]
                    
                    species[id_chromosome][id_gene] = [species[id_chromosome][id_gene][0],
                                                            species[id_chromosome][id_gene][1]+realR,
                                                            self.bayes((species[id_chromosome][id_gene][0],
                                                            species[id_chromosome][id_gene][1]+realR),data[1],id_chromosome)]
        def shift_mutate():
            while(round(random.random(),4)<shift_chance):
                    id_chromosome = random.randint(0,len(species)-1)
                    if(len(species[id_chromosome])<=2):return
                    type_extend = random.randint(0,1) #0 left, 1 right
                    if(type_extend==0):
                        id_gene = random.randint(1,len(species[id_chromosome])-2)
                        percentage = round(random.uniform(-0.9,0.9),4)
                        shift = min(species[id_chromosome][id_gene-1][1]-species[id_chromosome][id_gene-1][0],
                                    species[id_chromosome][id_gene+1][1]-species[id_chromosome][id_gene+1][0])*percentage
                        
                        species[id_chromosome][id_gene-1] = [species[id_chromosome][id_gene-1][0],
                                                                species[id_chromosome][id_gene-1][1]+shift,
                                                                self.bayes((species[id_chromosome][id_gene-1][0],
                                                                species[id_chromosome][id_gene-1][1]-shift),data[1],id_chromosome)]
                        
                        species[id_chromosome][id_gene] = [species[id_chromosome][id_gene][0]+shift,
                                                                species[id_chromosome][id_gene][1]+shift,
                                                                self.bayes((species[id_chromosome][id_gene][0]+shift,
                                                                species[id_chromosome][id_gene][1]+shift),data[1],id_chromosome)]

                        species[id_chromosome][id_gene+1] = [species[id_chromosome][id_gene+1][0]-shift,
                                                                species[id_chromosome][id_gene][1],
                                                                self.bayes((species[id_chromosome][id_gene][0]-shift,
                                                                species[id_chromosome][id_gene][1]),data[1],id_chromosome)]             
        def merge_mutate():
            while(round(random.random(),4)<merge_chance):
                id_chromosome = random.randint(0,len(species)-1)
                try:
                    id_gene = random.randint(0,len(species[id_chromosome])-2)
                    lbound = species[id_chromosome][id_gene][0]
                    rbound = species[id_chromosome][id_gene+1][1]
                    

                    species[id_chromosome][id_gene] = [lbound,rbound,
                                                    self.bayes([lbound,rbound],data[1],id_chromosome)]
                    del species[id_chromosome][id_gene+1]
                except:
                    pass
        def split_mutate():
            while(round(random.random(),4)<split_chance):
                id_chromosome = random.randint(0,len(species)-1)
                id_gene = random.randint(0,len(species[id_chromosome])-1)
                lbound = species[id_chromosome][id_gene][0]
                rbound = species[id_chromosome][id_gene][1]
                spbound = round(random.uniform(lbound,rbound),5)

                species[id_chromosome][id_gene] = [spbound,rbound,
                                                self.bayes([spbound,rbound],data[1],id_chromosome)]
                c = self.bayes([lbound,spbound],data[1],id_chromosome)
                species[id_chromosome].insert(id_gene,[lbound,spbound,c])
        def rebulit_mutate():
            while(round(random.random(),4)<rebuild_chance):
                id_chromosome = random.randint(0,len(species)-1)
                n_slice = random.randint(0,self.n_slice)
                lbound = data[0][id_chromosome][0]
                rbound = data[0][id_chromosome][1]
                
                temp_chromosome = []
                for k in range(n_slice):
                    sbound = round(random.uniform(lbound, rbound),4)
                    
                    temp_chromosome.append([lbound,sbound, self.bayes((lbound,sbound), data[1], id_chromosome)])
                    lbound = sbound
                temp_chromosome.append([lbound,rbound+1, self.bayes((lbound,rbound+1), data[1], id_chromosome)])
                
                temp_del = species[id_chromosome]
                species[id_chromosome] = temp_chromosome
                del temp_del
        def cheat():
            while(round(random.random(),4)<cheat_chance):
                id_chromosome = random.randint(0,len(species)-1)
                id_little_wong = random.randint(0,len(self.survived_biome)-1)
                
                temp_del = species[id_chromosome]
                species[id_chromosome] = self.survived_biome[id_little_wong][id_chromosome].copy()
                del temp_del
        def infected():
            while(round(random.random(),4)<infect_chance):
                id_chromosome = random.randint(0,len(species)-1)
                id_virus = random.randint(0,len(self.offspring)-1)
                
                temp_del = species[id_chromosome]
                species[id_chromosome] = self.offspring[id_virus][id_chromosome].copy()
                del temp_del
        def loss_mutate():
            while(round(random.random(),4)<loss_chance):
                id_chromosome = random.randint(0,len(species)-1)
                if(len(species[id_chromosome])>1):
                    id_gene = random.randint(0,len(species[id_chromosome])-1)
                    del species[id_chromosome][id_gene]
        def fracture_mutate():
            while(round(random.random(),4)<fracture_chance):
                id_chromosome = random.randint(0,len(species)-1)
                id_gene = random.randint(0,len(species[id_chromosome])-1)
                lbound = species[id_chromosome][id_gene][0]
                rbound = species[id_chromosome][id_gene][1]
                slbound = round(random.uniform(lbound,rbound),5)
                srbound = round(random.uniform(slbound,rbound),5)

                species[id_chromosome][id_gene] = [srbound,rbound,
                                                self.bayes([srbound,rbound],data[1],id_chromosome)]
                c = self.bayes([lbound,slbound],data[1],id_chromosome)
                species[id_chromosome].insert(id_gene,[lbound,slbound,c])

        extending_chance = 0.1
        shift_chance = 0.01
        split_chance = 0.3
        merge_chance = 0.7
        rebuild_chance = 0.05
        cheat_chance = 0.05
        infect_chance = 0.08
        loss_chance = 0.001
        fracture_chance = 0.001
        for species in self.offspring:
            extend_mutate()
            shift_mutate()
            merge_mutate()
            split_mutate()
            rebulit_mutate()
            cheat()
            infected()
            loss_mutate()
            fracture_mutate()
            
def preprocessing(data):
    """
    map data
    returns [ [[min1,max1],...], data]
    removes bad data which have 0
    """
    temp_data = data.copy()
    
    n_feature = len(temp_data[0].split(','))
    feature_range = [[1000000,0] for i in range(n_feature)]
    
    new_data = []
    
    for i in range(len(temp_data)):
        temp_data[i] = list(map(float,temp_data[i].split(',')))
        if(float(0) in temp_data[i][1:6] or float(0) == temp_data[i][7]):
            pass
        else:
            new_data.append(temp_data[i])
            for j in range(n_feature):
                if(temp_data[i][j] > feature_range[j][1]):
                    feature_range[j][1] = temp_data[i][j]
                if(temp_data[i][j] < feature_range[j][0]):
                    feature_range[j][0] = temp_data[i][j]
    return (feature_range,new_data)

def preprocessing_no_remove(data):
    """
    map data
    returns [ [[min1,max1],...], data]
    removes bad data which have 0
    """
    temp_data = data.copy()
    
    n_feature = len(temp_data[0].split(','))
    feature_range = [[1000000,0] for i in range(n_feature)]
    
    new_data = []
    
    for i in range(len(temp_data)):
        temp_data[i] = list(map(float,temp_data[i].split(',')))
        new_data.append(temp_data[i])
        for j in range(n_feature):
            if(temp_data[i][j] > feature_range[j][1]):
                feature_range[j][1] = temp_data[i][j]
            if(temp_data[i][j] < feature_range[j][0]):
                feature_range[j][0] = temp_data[i][j]
    return (feature_range,new_data)

def test_single_chromsome_single_validation(my_chromsome,data):
        information = data[:-1]
        target = data[-1]
        
        true_chance = 1
        false_chance = 1
        
        for feature_id in range(len(information)):
            if(information[feature_id] < my_chromsome[feature_id][0][0]):
                if(my_chromsome[feature_id][0][2][0]==0 and my_chromsome[feature_id][0][2][1]==0):
                    break
                else:
                    true_chance*=my_chromsome[feature_id][0][2][1]
                    false_chance*=my_chromsome[feature_id][0][2][0]
                    break
            elif(information[feature_id] >= my_chromsome[feature_id][-1][1]):
                if(my_chromsome[feature_id][-1][2][0]==0 and my_chromsome[feature_id][-1][2][1]==0):
                    break
                else:
                    true_chance*=my_chromsome[feature_id][-1][2][1]
                    false_chance*=my_chromsome[feature_id][-1][2][0]
                    break
            else:
                for fs in my_chromsome[feature_id]:
                    if(fs[0]<= information[feature_id] <fs[1]):
                        if(fs[0]==0 and fs[1]==0):
                            break
                        else:
                            true_chance*=fs[2][1]
                            false_chance*=fs[2][0]
                            break
        return [False,True][(false_chance<true_chance)==target]

def test_single_chromsome_total_validation(my_chromsome,data):
    n_total_data = len(data)
    n_correct = 0
    for i in data:
        final_result = test_single_chromsome_single_validation(my_chromsome,i)
        if(final_result):
            n_correct +=1
            
    return round(n_correct/n_total_data,5)
                    
def train(model: gene,epoch,whole_data,batch):
    def evolution(model:gene,data_load,times):
        model.Crossover()
        model.Cambrian_explosion(whole_data,30)
        model.mutation(whole_data)
        model.Darwin_time(data_load)
        print(f"{times} times evolution: heighest accuracy: {max(model.survived_score)}, mean accuracy: {round(sum(model.survived_score)/len(model.survived_score), 6)}")
        AGE_OF_EVOLUTION_HEIGHEST.append(max(model.survived_score))
        AGE_OF_EVOLUTION_MEAN.append(round(sum(model.survived_score)/len(model.survived_score), 5))
        AGE_OF_VALIDATION.append(test_single_chromsome_total_validation(biome.survived_biome[0],preprocessing_no_remove(data_test)[1]))
    
    biome.Cambrian_explosion(whole_data)
    biome.Darwin_time(whole_data[1])#initailize the data
    print(f"first time evolution: heighest accuracy: {max(model.survived_score)}, mean accuracy: {round(sum(model.survived_score)/len(model.survived_score), 6)}")
    
    AGE_OF_EVOLUTION_HEIGHEST.append(max(model.survived_score))
    AGE_OF_EVOLUTION_MEAN.append(round(sum(model.survived_score)/len(model.survived_score), 5))
    AGE_OF_VALIDATION.append(test_single_chromsome_total_validation(biome.survived_biome[0],preprocessing_no_remove(data_test)[1]))
    
    for i in range(1,epoch):
        evolution(model, whole_data[1],i+1)

data_path_train = os.path.join("diabetes_data","diabetes_data","experimentA","train_data.csv")
feature_name = []
epoch = 30
AGE_OF_EVOLUTION_HEIGHEST = []
AGE_OF_EVOLUTION_MEAN = []
AGE_OF_VALIDATION = []

#Train data load and preprocessing
data_train = []
with open(data_path_train, newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
    for row in spamreader:
        data_train.append(row[0])

feature_name = data_train[0].split(',')
print(feature_name)
data_train.pop(0)
data_train = preprocessing(data_train)
#load test
data_test = []
data_path_test = os.path.join("diabetes_data","diabetes_data","experimentA","test_data.csv")
with open(data_path_test, newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
    for row in spamreader:
        data_test.append(row[0])
data_test.pop(0)

biome = gene()
train(biome,epoch,data_train,10)


print("test result:",test_single_chromsome_total_validation(biome.survived_biome[0],preprocessing_no_remove(data_test)[1]))
print("test result:",test_single_chromsome_total_validation(biome.survived_biome[0],preprocessing(data_test)[1]))

temp = [i for i in range(epoch)]
# print(temp)
# print(AGE_OF_EVOLUTION_HEIGHEST)
plt.plot([i for i in range(epoch)], AGE_OF_EVOLUTION_HEIGHEST, color='red')
plt.plot([i for i in range(epoch)], AGE_OF_EVOLUTION_MEAN,color='blue')
plt.plot([i for i in range(epoch)], AGE_OF_VALIDATION,color='orange')
plt.xlabel("age")
plt.ylabel("accuracy")
plt.legend(["Heighest accuracy","Mean accuracy","test accuracy"])
plt.show()