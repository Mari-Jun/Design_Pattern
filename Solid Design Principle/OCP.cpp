// OCP : (Open Closed Principle) 열림 닫힘 원칙

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Line {top, jug, mid, bot, spt};
enum class Group {slayer, fighter, mage, marksman, controller, tank};

struct Champion
{
	string name;
	Line line;
	Group group;
};

//비효율적인 방법
struct ChampionFilter
{
	using Champs = vector<Champion*>;

	Champs filter_by_line(const Champs& champs, const Line line)
	{
		Champs result;
		for (auto& champ : champs)
			if (champ->line == line)
				result.push_back(champ);
		return result;
	}

	Champs filter_by_group(const Champs& champs, const Group group)
	{
		Champs result;
		for (auto& champ : champs)
			if (champ->group == group)
				result.push_back(champ);
		return result;
	}
};

//효율적으로 코딩하기 위한 OCP

template <typename T> struct MultiSpecification;

template <typename T> struct Specification
{
	virtual bool is_satisfied(T* item) = 0;

	MultiSpecification<T> operator&&(Specification&& other)
	{
		return MultiSpecification<T>(*this, other);
	}
};

template <typename T> struct MultiSpecification : Specification<T>
{
	MultiSpecification(Specification<T>& first, Specification<T>& second)
		: first(first), second(second) {}

	Specification<T>& first;
	Specification<T>& second;

	bool is_satisfied(T* item) override
	{
		return first.is_satisfied(item) && second.is_satisfied(item);
	}
};


template <typename T> struct Filter
{
	virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0;
};

struct ChampFilter : Filter<Champion>
{
	vector<Champion*> filter(vector<Champion*> champs, Specification<Champion>& spec) override
	{
		vector<Champion*> result;
		for (auto& champ : champs)
			if (spec.is_satisfied(champ))
				result.push_back(champ);
		return result;
	}
};

struct LineSpecification : Specification<Champion>
{
	LineSpecification(Line line) : line(line) {}

	Line line;

	bool is_satisfied(Champion* champ) override
	{
		return champ->line == line;
	}
};

struct GroupSpecification : Specification<Champion>
{
	GroupSpecification(Group group) : group(group) {}

	Group group;

	bool is_satisfied(Champion* champ) override
	{
		return champ->group == group;
	}
};

int main()
{
	Champion akali{ "Akali", Line::mid, Group::slayer };
	Champion sylas{ "Sylas", Line::mid, Group::mage };
	Champion lulu{ "Lulu", Line::spt, Group::controller };
	Champion fizz{ "Fizz", Line::mid, Group::slayer };

	vector<Champion*> champs{ &akali, &sylas, &lulu, &fizz};


	ChampFilter cf;
	LineSpecification mid(Line::mid);

	for (auto& champ : cf.filter(champs, mid))
		cout << champ->name << " is mid line\n";

	auto spec = LineSpecification{ Line::mid } && GroupSpecification{ Group::slayer };
	for (auto& champ : cf.filter(champs, spec))
		cout << champ->name << " is mid line and slayer\n";
}