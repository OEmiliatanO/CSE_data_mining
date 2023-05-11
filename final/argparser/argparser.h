#include <vector>
#include <unordered_map>
#include <string>

class argparser
{
public:
	argparser() = default;
	
	std::vector<std::string> to_parse;
	std::unordered_map<std::string, std::string> args;

	void parse(std::size_t argc, char **argv);
	void add(std::string arg);
};

void argparser::add(std::string arg)
{
	to_parse.emplace_back(arg);
}

void argparser::parse(std::size_t argc, char **argv)
{
	for (std::size_t i = 1; i < argc; ++i)
	{
		std::string arg{argv[i]};
		for (std::size_t j = 0; j < to_parse.size(); ++j)
			if (arg == to_parse[j])
			{
				args[arg] = argv[++i];
				break;
			}
	}
}
