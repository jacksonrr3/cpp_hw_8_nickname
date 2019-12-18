#pragma once

#include <iostream>
#include <array>
#include <unordered_map>
#include <memory>
#include <string>
#include <algorithm>

//класс, реализуюий структуру RadixTree для хранения различных вариантов имен
class RadixTrie {

	//вспомогательный класс для реализации листа дерева.
	class Node {
		std::string _lable;     //хранит часть слова
		bool _end = true;		//обозначение окончания слова
		std::unordered_map<char, std::unique_ptr<Node>> _children; //указатели на возможные "продолжения" слова

		void add_new_child(std::string&& str) {
			if (_children[str[0]]) {
				_children[str[0]]->add(str);
			}
			else {
				_children[str[0]] = std::make_unique<Node>(Node(str));
			}
		}

	public:
		Node() {}
		Node(const std::string& str) :_lable(str) {}

		const std::string get_lable() {
			return _lable;
		}

		bool get_end() const {
			return _end;
		}

		//метод добавления нового слова
		void add(const std::string& str) {
			auto it = std::mismatch(_lable.begin(), _lable.end(), str.begin(), str.end());
			if (it.first != _lable.end()) {
				auto new_Node = std::make_unique<Node>(std::string(it.first, _lable.end()));
				_end = false;
				std::swap(_children, new_Node->_children);
				_children[*it.first] = std::move(new_Node);
				_lable.erase(it.first, _lable.end());
			}

			if (it.second != str.end()) {
				add_new_child(std::string(it.second, str.end()));
			}

			_end = (_children.empty() || (it.second == str.end()));
		}

		void print_node(size_t level) {
			for (size_t i = 0; i < level; i++) {
				std::cout << " ";
			}
			std::cout << _lable;
			if (_end) { std::cout << "$"; }
			std::cout << std::endl;
			std::for_each(_children.begin(), _children.end(), [level](auto& it) {
				it.second->print_node(level + 1); });
		}

		void print_name(std::string& name, std::string& pref) {
			pref = (name.empty()) ? _lable : name + _lable[0];

			name += _lable;
			if (_end) {std::cout << name << " " << pref << std::endl;}

			if (!(_children.empty())) {
				std::for_each(_children.begin(), _children.end(), [&name, &pref](auto& it) {
					it.second->print_name(name, pref); });
			}
			
			if (_end) { pref.pop_back(); }
			else {
				size_t pos = pref.find(_lable);
				std::string temp = pref.substr(0, pos);
				pref = std::move(temp);
			}
			name = pref;
			

		}
	
	};

	//корневой лист дерева
	std::unique_ptr<Node> _root;

public:

	RadixTrie():_root(nullptr) {}

	void append(const std::string& label) {
		if (_root == nullptr) {
			_root = std::make_unique<Node>(label);
		}
		else {
			_root->add(label);
		}
	}

	void print_tree() {
		if (_root){
			int level = 0;
			_root->print_node(level);
		}
	}

	void print_names() {
		if (_root) {
			std::string name;
			std::string pref;
			_root->print_name(name, pref);
		}
	}

};
