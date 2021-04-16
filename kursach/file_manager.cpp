#include "file_manager.h"

FileManager::FileManager()
{
	create("group");
	create("lecturer");
}

int FileManager::create(std::string file_name)
{
	std::ofstream file(file_name);
	file.close();

	return 0;
}

int FileManager::empty(std::string file_name)
{
	std::ofstream file;
	file.open(file_name, std::ofstream::out | std::ofstream::trunc);

	if (!file)
	{
		std::cout << "File Error:\n";
		return 1;
	}

	file.close();
}

int FileManager::get_file_size(std::fstream &f)
{
	int size;
	f.seekg(0, std::ios::end);
	size = f.tellg();
	f.seekg(0, 0);

	return size;
}

int FileManager::write(Group &item)
{
	std::ofstream file;

	file.open("group", std::ios::app | std::ios::binary);

	if (!file)
	{
		std::cout << "File Error:\n";
		return 1;
	}

	file.write(reinterpret_cast<char*>(&item), sizeof(item));

	file.close();
}

int FileManager::write(Lecturer &item)
{
	std::ofstream file;
	file.open("lecturer", std::ios::app | std::ios::binary);

	if (!file)
	{
		std::cout << "File Error:\n";
		return 1;
	}

	file.write(reinterpret_cast<char*>(&item), sizeof(item));

	file.close();
}

int FileManager::read(std::vector<Group> &list)
{
	std::fstream file("group", std::ios::in | std::ios::binary);
	Group item;
	int file_size;

	if (!file)
	{
		std::cout << "File Error:\n";
		return 1;
	}

	file_size = get_file_size(file);

	while (file_size != file.tellg())
	{
		file.read((char*)& item, sizeof(item));
		list.push_back(item);
	}

	file.close();
}

int FileManager::read(std::vector<Lecturer> &list)
{
	std::fstream file("lecturer", std::ios::in | std::ios::binary);
	Lecturer item;
	int file_size;

	if (!file)
	{
		std::cout << "File Error:\n";
		return 1;
	}

	file_size = get_file_size(file);

	while (file_size != file.tellg())
	{
		file.read((char*)& item, sizeof(item));
		list.push_back(item);
	}

	file.close();
}