#pragma once 
#include <string> 
#include <iostream> 

using std::string;
using std::cout;
using std::endl;

const int MAX_DEG = 10;// Максимальная степень минус 1 


class Monom
{
private:

	string monom;

	void make_string()
	{
		int a, b, c;
		a = d / 100;
		b = (d / 10) % 10;
		c = d % 10;

		if (k == 0)
		{
			monom = "0";
		}
		else
		{
			monom = "";
			if (k != 1 && k != -1)
				monom = int_to_string(k);

			if (a != 0)
			{
				if (monom != "")
					monom += "*";
				monom += "x";
				if (a != 1)
					monom += "^" + int_to_string(a);
			}
			if (b != 0)
			{
				if (monom != "")
					monom += "*";
				monom += "y";
				if (b != 1)
					monom += "^" + int_to_string(b);
			}
			if (c != 0)
			{
				if (monom != "")
					monom += "*";
				monom += "z";
				if (c != 1)
					monom += "^" + int_to_string(c);
			}
			if (k == -1)
				monom = "-" + monom;
		}
	}

	void set_var(char var, string num)
	{
		if (num == "-")
			num += "1";

		switch (var)
		{
		case ' ':
			k = std::stod(num);
			break;

		case 'x':
			if (num == "")
				num = "1";
			d += std::stod(num) * MAX_DEG * MAX_DEG;
			break;

		case 'y':
			if (num == "")
				num = "1";
			d += std::stod(num) * MAX_DEG;
			break;

		case 'z':
			if (num == "")
				num = "1";
			d += std::stod(num);
			break;
		}

		//cout « endl « "----------" « endl « "'" « var « "' '" « num « "' " « k « ' ' « d « endl« "----------" « endl; 

	}

	string int_to_string(int a)
	{
		string res = "";
		string sgn = "";
		if (a < 0)
			sgn = "-";
		a = abs(a);
		while (a != 0)
		{
			res = char((a % 10) + 48) + res;
			a /= 10;
		}
		res = sgn + res;
		return res;
	}

public:

	int d;
	int k;

	Monom()
	{
		monom = "0";
		d = 0;
		k = 0;
	}

	Monom(int new_k, int new_d)
	{
		k = new_k;
		d = new_d;
		make_string();
	}

	void check()
	{
		k = 1;
		d = 0;
		int status = 0;
		string num;
		char var = ' ';

		if (monom == "")
			throw 1;



		for (int i = 0; i < monom.size(); i++)
		{
			//0 - минус,число, переменная 
			//1 - число,переменная, умножить 
			//2 - число, степень, умножить, переменная 
			//3 - переменная 
			//4 - число 

			//cout « endl « i « " : '" « monom[i] « "' Status = " « status « endl; 


			if (monom[i] == ' ')
				continue;


			switch (status)
			{
			case 0:

				if (monom[i] == '-' || (monom[i] >= '0' && monom[i] <= '9'))
				{
					num += monom[i];
					status = 1;
				}
				else if (monom[i] == 'x' || monom[i] == 'y' || monom[i] == 'z')
				{
					var = monom[i];
					status = 2;
				}
				else
				{
					status = -1;
				}

				break;

			case 1:

				if (monom[i] >= '0' && monom[i] <= '9')
				{
					num += monom[i];
					status = 1;
				}
				else if (monom[i] == 'x' || monom[i] == 'y' || monom[i] == 'z')
				{
					set_var(var, num);
					num = "";
					var = monom[i];
					status = 2;
				}
				else if (monom[i] == '*')
				{
					status = 3;
				}

				break;

			case 2:

				if (monom[i] >= '0' && monom[i] <= '9')
				{
					num += monom[i];
					status = 1;
				}
				else if (monom[i] == '^')
				{
					status = 4;
				}
				else if (monom[i] == '*')
				{
					status = 3;
				}
				else if (monom[i] == 'x' || monom[i] == 'y' || monom[i] == 'z')
				{
					set_var(var, num);
					num = "";
					var = monom[i];
					status = 2;
				}
				else
				{
					status = -1;
				}

				break;

			case 3:

				if (monom[i] == 'x' || monom[i] == 'y' || monom[i] == 'z')
				{
					set_var(var, num);
					num = "";
					var = monom[i];
					status = 2;
				}
				else
				{
					status = -1;
				}

				break;

			case 4:

				if (monom[i] >= '0' && monom[i] <= '9')
				{
					num += monom[i];
					status = 1;
				}
				else
				{
					status = -1;
				}

				break;

			case -1:

				throw 1;
			}
		}

		int n = monom.size() - 1;
		if (monom[n] == '-' || monom[n] == '^' || monom[n] == '*')
			throw 1;
		set_var(var, num);
	}

	Monom(string new_monom)
	{
		monom = new_monom;
		check();
		make_string();
	}

	Monom operator*(Monom mon)
	{
		Monom res(k * mon.k, d + mon.d);
		return res;
	}

	Monom operator+(Monom a)
	{
		if (d == a.d)
		{
			Monom res;
			res.d = d;
			res.k = k + a.k;
			res.make_string();
			return res;
		}
		else
			throw 1;
	}

	string get_string()
	{
		make_string();
		return monom;
	}

};

class Node
{
public:
	Monom val;
	Node* next;
};

class Iterator
{
private:
	Node *a;

public:

	Iterator()
	{
		a = NULL;
	}

	Iterator(Node *x)
	{
		a = x;
	}

	Iterator operator++()
	{
		a = a->next;
		return *this;
	}

	bool operator!=(Node* x)
	{
		return a != x;
	}

	bool operator==(Node* x)
	{
		return a == x;
	}

	Monom operator*()
	{
		return a->val;
	}

};

class List
{
private:

	Node* head;

public:
	List()
	{
		head = new Node;
		head->next = NULL;
	}

	List(const List &a)
	{
		head = new Node;
		Node* i = a.head;
		Node* tmp = head;
		while (i->next != NULL)
		{
			tmp->val = i->val;
			tmp->next = new Node;
			i = i->next;
			tmp = tmp->next;
		}
		tmp->val = i->val;
		tmp->next = NULL;
	}

	void push(Monom a)
	{
		if (head->next == NULL)
		{
			if (a.d == 0)
			{
				head->val.k += a.k;
			}
			else
			{
				Node *x = new Node;
				head->next = x;
				x->val = a;
				x->next = NULL;
			}
			return;
		}
		Node *tmp = head;
		while (tmp->next != NULL && tmp->next->val.d < a.d)
		{
			tmp = tmp->next;
		}
		if (tmp->next == NULL)
		{
			Node *x = new Node;
			tmp->next = x;
			x->next = NULL;
			x->val = a;
			return;
		}
		if (tmp->next->val.d == a.d)
		{
			tmp->next->val.k += a.k;
		}
		else
		{
			Node *x = new Node;
			x->next = tmp->next;
			tmp->next = x;
			x->val = a;
		}
	}

	void pop(Monom a)
	{
		Node* i = head;
		while (i->next->val.d < a.d)
			i = i->next;
		if (i->next->val.d == a.d)
		{
			Node* tmp = i->next;
			i->next = tmp->next;
			delete tmp;
		}
		else
			throw 1;
	}

	friend std::ostream& operator<<(std::ostream& out, const List &a)
	{
		Iterator i(a.head);
		while (i != NULL)
		{
			out <<(*i).get_string() << ' ';
			++i;
		}
		return out;
	}

	Iterator begin()
	{
		return Iterator(head);
	}

};

class Polinom
{
private:

	List a;
	string polinom;

public:

	Polinom()
	{
		polinom = "0";
	}

	Polinom(string new_polinom)
	{
		polinom = new_polinom;
		string s = "";

		for (int i = 0; i < polinom.size(); i++)
		{
			if (polinom[i] == '-')
			{
				a.push(s);
				s = "";
			}
			else if (polinom[i] == '+')
			{
				a.push(s);
				s = "";
				continue;
			}
			s += polinom[i];
		}
		a.push(s);

		polinom = "";
		Iterator i = a.begin();
		while (i != NULL)
		{
			if ((*i).k == 0)
			{
				++i;
				continue;
			}
			else if (polinom == "")
			{
				polinom += (*i).get_string();
			}
			else
			{
				if ((*i).get_string()[0] == '-')
				{
					polinom += " - ";
					for (int j = 1; j < (*i).get_string().size(); j++)
					{
						polinom += (*i).get_string()[j];
					}
				}
				else
				{
					polinom += " + ";
					polinom += (*i).get_string();
				}
			}
			++i;
		}

	}

	Polinom(List l)
	{
		a = l;
		polinom = "";
		Iterator i = a.begin();
		while (i != NULL)
		{
			if ((*i).k == 0)
			{
				++i;
				continue;
			}
			else if (polinom == "")
			{
				polinom += (*i).get_string();
			}
			else
			{
				if ((*i).get_string()[0] == '-')
				{
					polinom += " - ";
					for (int j = 1; j < (*i).get_string().size(); j++)
					{
						polinom += (*i).get_string()[j];
					}
				}
				else
				{
					polinom += " + ";
					polinom += (*i).get_string();
				}
			}
			++i;
		}
	}

	void push(Monom mon)
	{
		a.push(mon);
		polinom = Polinom(a).polinom;
	}

	Polinom operator+(Polinom pol)
	{
		/*List l;
		Iterator i1 = a.begin();
		Iterator i2 = pol.a.begin();
		while (i1 != NULL && i2 != NULL)
		{
			if ((*i1).d == (*i2).d)
			{
				l.push(*i1 + *i2);
				++i1;
				++i2;
			}
			else if ((*i1).d < (*i2).d)
			{
				l.push(*i1);
				++i1;
			}
			else
			{
				l.push(*i2);
				++i2;
			}
		}
		if (i1 == NULL)
		{
			while (i2 != NULL)
			{
				l.push(*i2);
				++i2;
			}
		}
		else
		{
			while (i1 != NULL)
			{
				l.push(*i1);
				++i1;
			}
		}
		return l;*/

		Polinom res(polinom + " + " + pol.polinom);
		return res;

	}

	Polinom operator*(Polinom pol)
	{
		Polinom res;
		for (Iterator i = a.begin(); i != NULL; ++i)
		{
			for (Iterator j = pol.a.begin(); j != NULL; ++j)
			{
				res.push((*i) * (*j));
			}
		}
		return Polinom(res.a);
	}

	bool operator==(const Polinom pol) const
	{
		return polinom == pol.polinom;
	}

	friend std::ostream& operator<<(std::ostream& out, const Polinom &pol)
	{
		out << pol.polinom;
		return out;
	}

};