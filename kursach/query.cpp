#include "query.h"

QueryParser::QueryParser()
{
}

void QueryParser::print_vector()
{
	for (int i = 0; i < query.size(); i++)
	{
		std::cout << query[i] << std::endl;
	}
}

std::string QueryParser::upper(const std::string &str)
{
	std::string str_tmp = str;
	std::transform(str_tmp.begin(), str_tmp.end(), str_tmp.begin(), ::toupper);

	return str_tmp;
}

void QueryParser::write_query()
{
	query.clear();

	std::string word="";

	while (std::cin >> word)
	{
		if (word != "go")
		{
			query.push_back(word);
		}
		else
		{
			break;
		}
	}
}

int QueryParser::parse_query()
{
	std::string function;
	int error = 0;

	function = upper(query[0]);

	if (function == "ADD")
	{
		error = add();
	}
	else if (function == "SELECT")
	{
		error = select();
	}
	else if (function == "DELETE") 
	{
		error = del();
	}
	else
	{
		return 1;
	}
	
	return error;
}

int QueryParser::get_table_name(std::string & table_name, int &index)
{
	std::string item, tmp="";
	int item_count, total_count=0, count=0;
	for (int i = 1; i < query.size(); i++)
	{
		count++;
		item = query[i];
		item_count = std::count(item.begin(), item.end(), '"');
		total_count += item_count;

		if ((i == 1 && (item_count == 0 || item_count > 2))|| total_count > 2)
		{
			return 1;
		}

		tmp += item;

		if (total_count == 2)
		{
			if (tmp.size() != 2)
			{
				index = i;
				table_name = tmp.substr(1, tmp.size() - 2);
				return 0;
			}
			else
			{
				return 1;
			}
		}
	}

	if (count > 0)
	{
		return 1;
	}

	return 0;
}

int QueryParser::check_table_name(const std::string &table_name)
{
	if (table_name == "group" || table_name == "lecturer")
	{
		return 0;
	}
	else
	{
		return 1;
	}

}

int QueryParser::parse_condition(std::string condition, std::string &key, ConStruct &con)
{
	int index_of_equally;
	std::string syumbol = "=";

	if (std::count(condition.begin(), condition.end(), '=') == 1)
	{
		index_of_equally = condition.find('=');

		if (condition.substr(index_of_equally - 1, 1) == "!")
		{
			syumbol = "!=";
		}

		key = condition.substr(0, index_of_equally);
		con.value = condition.substr(index_of_equally + 1 + syumbol.size(), condition.size() - key.size() - (2 + syumbol.size()));
		con.syumbol = syumbol;

		if (key.size() == 0 || con.value.size() == 0)
		{
			return 1;
		}
	}
	else
	{
		return 1;
	}

	return 0;
}

int QueryParser::get_condition(int index, Maptype &condition)
{

	std::string function;
	std::string key, item, tmp = "", syumbol;
	ConStruct con;
	int item_count, total_count = 0, count = 0;

	if (query.size() == index + 1)
	{
		return 0;
	}

	function = upper(query[index + 1]);
	
	if (function == "WHERE")
	{
		for (int i = index + 2; i < query.size(); i++)
		{
			item = query[i];
			item_count = std::count(item.begin(), item.end(), '"');
			total_count += 2;
			
			tmp += item;
			count++;

			if (total_count == 2)
			{
				if (parse_condition(tmp, key, con))
				{
					return 1;
				}
				
				condition[key] = con;

				tmp = "";
				total_count = 0;
				count = 0;

				if (i != query.size() - 1)
				{
					function = upper(query[i + 1]);
					i++;
					if (function != "AND")
					{
						return 1;
					}
				}
			}
		}

		if (count > 0)
		{
			return 1;
		}
	}
	else
	{
		return 1;
	}

	return 0;
}

int QueryParser::add()
{
	std::string table_name, item;
	int index, error = 0;

	if (get_table_name(table_name, index))
	{
		return 1;
	}

	if (index != query.size() - 1 || check_table_name(table_name))
	{
		return 1;
	}

	if (table_name == "group")
	{
		Group gr;
		gr.set();
		error += file.append(gr);
	}
	else if (table_name == "lecturer")
	{
		Lecturer le;
		le.set();
		error += file.append(le);
	}

	return error;
}

int QueryParser::select()
{
	std::string table_name;
	int index, error = 0;
	Maptype condition;

	if (get_table_name(table_name, index))
	{
		return 1;
	}

	if (check_table_name(table_name))
	{
		return 1;
	}
	
	if (get_condition(index, condition))
	{
		return 1;
	}

	if (table_name == "group")
	{
		std::vector<Group> gr_list;
		error += file.read(gr_list);
		Group::check_condition(condition);

		for (int i = 0; i < gr_list.size(); i++)
		{
			if (gr_list[i].filter(condition))
			{
				gr_list[i].print();
			}

		}
	}
	else if (table_name == "lecturer")
	{
		std::vector<Lecturer> le_list;
		error += file.read(le_list);
	}

	



	return 0;
}

int QueryParser::del()
{
	return 0;
}

