#pragma once
#include <ostream>
#include <sstream>
namespace rut::cip 
{
	template <typename T> struct Node;

	template <typename T>
	std::ostream& operator<<(std::ostream& out, const Node<T>& node);

	template <typename T>
	struct Node
	{
		T data;
		Node* parent;
		Node* left;
		Node* right;

		Node(const T& value);
		Node(const Node& other) = delete;
		Node(Node&& other) noexcept = default;
		Node& operator=(const Node& other) = delete;
		Node& operator=(Node&& other) noexcept = default;
		~Node();

		bool IsRoot() const;
		bool IsLeaf() const;
		friend auto operator<=>(const Node& lha, const Node& rha)
		{
			if (std::less<T>()(lha.data, rha.data))
			{
				return 1;
			}

			if (std::greater<T>()(lha.data, rha.data))
			{
				return -1;
			}

			return 0;
		}

		friend bool operator==(const Node& lha, const Node& rha)
		{
			return (operator<=>(lha, rha) == 0);
		}
	};
	template<typename T>
	inline Node<T>::Node(const T& value)
		: data{ value }, parent{nullptr}, left{nullptr}, right{nullptr}
	{
	}

	template<typename T>
	inline Node<T>::~Node()
	{
		if (!this->IsRoot())
		{
			if (this == this->parent->left)
			{
				this->parent->left = nullptr;
			}
			else
			{
				this->parent->right = nullptr;
			}
		}

		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
	}

	template<typename T>
	inline bool Node<T>::IsRoot() const
	{
		return nullptr == this->parent;
	}

	template<typename T>
	inline bool Node<T>::IsLeaf() const
	{
		return nullptr == this->left && nullptr == this->right;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& out, const Node<T>& node)
	{
		std::stringstream buffer{};
		buffer << node.data;
		out << buffer.str();
		return out;
	}

}