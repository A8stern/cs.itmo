#include "LN.h"

#include <fstream>
#include <vector>

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		fprintf(stderr, "Expected 3 arguments but found %i\n", argc - 1);
		return ERROR_PARAMETER_INVALID;
	}
	std::string arg3 = argv[3];
	std::string d = "direct";
	std::string in = "inverse";
	if (arg3 != d && arg3 != in)
	{
		fprintf(stderr, "Wrong third argument");
		return ERROR_PARAMETER_INVALID;
	}
	std::vector< LN > stack;
	std::ifstream fin(argv[1]);
	if (!fin)
	{
		fprintf(stderr, "File %s not found\n", argv[1]);
		return ERROR_CANNOT_OPEN_FILE;
	}
	std::string buff;
	while (fin >> buff)
	{
		if (buff.empty())
		{
			break;
		}
		if (buff == "+")
		{
			LN first = stack[stack.size() - 1];
			stack.pop_back();
			LN second = stack[stack.size() - 1];
			stack.pop_back();
			stack.push_back(first + second);
		}
		else if (buff == "-")
		{
			LN first = stack[stack.size() - 1];
			stack.pop_back();
			LN second = stack[stack.size() - 1];
			stack.pop_back();
			if (arg3 == d)
			{
				stack.push_back(first - second);
			}
			else
			{
				stack.push_back(second - first);
			}
		}
		else if (buff == "*")
		{
			LN first = stack[stack.size() - 1];
			stack.pop_back();
			LN second = stack[stack.size() - 1];
			stack.pop_back();
			stack.push_back(first * second);
		}
		else if (buff == "/")
		{
			LN first = stack[stack.size() - 1];
			stack.pop_back();
			LN second = stack[stack.size() - 1];
			stack.pop_back();
			if (arg3 == d)
			{
				stack.push_back(first / second);
			}
			else
			{
				stack.push_back(second / first);
			}
		}
		else if (buff == "%")
		{
			LN first = stack[stack.size() - 1];
			stack.pop_back();
			LN second = stack[stack.size() - 1];
			stack.pop_back();
			if (arg3 == d)
			{
				stack.push_back(first % second);
			}
			else
			{
				stack.push_back(second % first);
			}
		}
		else if (buff == "~")
		{
			LN first = stack[stack.size() - 1];
			stack.pop_back();
			stack.push_back(~first);
		}
		else if (buff == "_")
		{
			LN first = stack[stack.size() - 1];
			stack.pop_back();
			stack.push_back(-first);
		}
		else if (buff == "<")
		{
			LN first = stack[stack.size() - 1];
			stack.pop_back();
			LN second = stack[stack.size() - 1];
			stack.pop_back();
			if (first.isNull())
			{
				stack.push_back(first);
			}
			else if (second.isNull())
			{
				stack.push_back(second);
			}
			else
			{
				if (first < second)
				{
					if (arg3 == d)
					{
						stack.push_back(LN(1));
					}
					else
					{
						stack.push_back(LN("0"));
					}
				}
				else
				{
					if (arg3 == d)
					{
						stack.push_back(LN("0"));
					}
					else
					{
						stack.push_back(LN(1));
					}
				}
			}
		}
		else if (buff == "<=")
		{
			LN first = stack[stack.size() - 1];
			stack.pop_back();
			LN second = stack[stack.size() - 1];
			stack.pop_back();
			if (first.isNull())
			{
				stack.push_back(first);
			}
			else if (second.isNull())
			{
				stack.push_back(second);
			}
			else
			{
				if (first <= second)
				{
					if (arg3 == d)
					{
						stack.push_back(LN(1));
					}
					else
					{
						stack.push_back(LN("0"));
					}
				}
				else
				{
					if (arg3 == d)
					{
						stack.push_back(LN("0"));
					}
					else
					{
						stack.push_back(LN(1));
					}
				}
			}
		}
		else if (buff == ">")
		{
			LN first = stack[stack.size() - 1];
			stack.pop_back();
			LN second = stack[stack.size() - 1];
			stack.pop_back();
			if (first.isNull())
			{
				stack.push_back(first);
			}
			else if (second.isNull())
			{
				stack.push_back(second);
			}
			else
			{
				if (first > second)
				{
					if (arg3 == d)
					{
						stack.push_back(LN(1));
					}
					else
					{
						stack.push_back(LN("0"));
					}
				}
				else
				{
					if (arg3 == d)
					{
						stack.push_back(LN("0"));
					}
					else
					{
						stack.push_back(LN(1));
					}
				}
			}
		}
		else if (buff == ">=")
		{
			LN first = stack[stack.size() - 1];
			stack.pop_back();
			LN second = stack[stack.size() - 1];
			stack.pop_back();
			if (first.isNull())
			{
				stack.push_back(first);
			}
			else if (second.isNull())
			{
				stack.push_back(second);
			}
			else
			{
				if (first >= second)
				{
					if (arg3 == d)
					{
						stack.push_back(LN(1));
					}
					else
					{
						stack.push_back(LN("0"));
					}
				}
				else
				{
					if (arg3 == d)
					{
						stack.push_back(LN("0"));
					}
					else
					{
						stack.push_back(LN(1));
					}
				}
			}
		}
		else if (buff == "==")
		{
			LN first = stack[stack.size() - 1];
			stack.pop_back();
			LN second = stack[stack.size() - 1];
			stack.pop_back();
			if (first.isNull())
			{
				stack.push_back(first);
			}
			else if (second.isNull())
			{
				stack.push_back(second);
			}
			else
			{
				if (first == second)
				{
					stack.push_back(LN(1));
				}
				else
				{
					stack.push_back(LN("0"));
				}
			}
		}
		else if (buff == "!=")
		{
			LN first = stack[stack.size() - 1];
			stack.pop_back();
			LN second = stack[stack.size() - 1];
			stack.pop_back();
			if (first.isNull())
			{
				stack.push_back(first);
			}
			else if (second.isNull())
			{
				stack.push_back(second);
			}
			else
			{
				if (first != second)
				{
					stack.push_back(LN(1));
				}
				else
				{
					stack.push_back(LN("0"));
				}
			}
		}
		else
		{
			stack.emplace_back(buff.c_str());
		}
		if (stack[stack.size() - 1].hasMem())
		{
			fprintf(stderr, "Troubles with memory");
			return ERROR_OUT_OF_MEMORY;
		}
	}
	fin.close();
	std::ofstream fout(argv[2]);
	if (!fout)
	{
		fprintf(stderr, "File %s not found\n", argv[2]);
		return ERROR_CANNOT_OPEN_FILE;
	}
	for (int i = stack.size() - 1; i >= 0; i--)
	{
		char *temp = stack[i].appear();
		fout << temp << std::endl;
	}
	fout.close();
	return 0;
}
