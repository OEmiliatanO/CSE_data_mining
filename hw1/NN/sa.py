from random import sample, shuffle, uniform, randint
import numpy as np
from math import exp
# import matplotlib.pyplot as plt
# N=100
# MAXT=1000
# MINT=0.01
# RATE=0.99
# K=50

def sa(N,MAXT,MINT,RATE,K,LNMA,LNMI,solu_func):
    SAMPLE_LIST=[i for i in range(1,N)]
    solution=[randint(LNMI,LNMA) for i in range(N)]
    def change(solution):
        pos=sample(SAMPLE_LIST,2)
        solution[pos[0]],solution[pos[1]]=solution[pos[1]],solution[pos[0]]
    def change2(solution):
        pos=randint(0,N-1)
        solution[pos]=randint(LNMI,LNMA)
    print("Start\n=================\n",end="")
    print(solution)
    end_max=solu_func(solution)
    t=MAXT
    # dislist=[end_max]
    # print("i:",solution)
    # print("i dis:",end_max)
    while t>MINT:
        for k in range(K):
            solution2=solution.copy()
            if k%2==0:
                change(solution2)
            else:
                change2(solution2)
            print(t,k,"\n=================\n",end="")
            
            new_max=solu_func(solution2)
            diff = new_max - end_max
            print(new_max,end_max,diff,exp(-diff/t))
            if diff<=0:
                solution=solution2
                end_max=new_max
            else:
                prob=exp(-diff/t)
                randnum=uniform(0,1)
                if randnum<prob:
                    solution=solution2
                    end_max=new_max
                else:
                    pass
        t*=RATE
        # dislist.append(end_max)
    # print(solution)
    # print(end_max)
    # plt.figure(figsize = (15,8))
    # plt.xlabel("Iteration",fontsize = 15)
    # plt.ylabel("Distance",fontsize = 15)

    # plt.plot(dislist,linewidth = 2.5, label = "Everytime smallest distance", color = 'r')
    # plt.legend()
    # plt.show(block=False)
    # plt.pause(2)
    # plt.close()
    return solution
# for i in range(10):
#     solution=sa(1)
    # sa(-1,solution)