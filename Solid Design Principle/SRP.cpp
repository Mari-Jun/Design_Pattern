// SRP : (Single Responsibility Principle) 단일 책임 원칙

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <string_view>

using namespace std;

struct Book
{
	explicit Book(string_view title) : title{ title } {}

	void AddSentence(const string& sentence);

	string title;
	vector<string> sentences;
};

void Book::AddSentence(const string& sentence)
{
	sentences.push_back(sentence);
}

struct Library
{
	static void save(const Book& book, const string& filename)
	{
		ofstream out{ filename };
		for (auto& sentence : book.sentences)
			out << sentence << endl;
	}
};

int main()
{
	Book book{ "SRP" };
	book.AddSentence("Single");
	book.AddSentence("Responsibility");
	book.AddSentence("Principle");

	Library::save(book, "book.txt");
}


