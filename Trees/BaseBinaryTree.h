#pragma once
#include <vector>
#include <sstream>
#include "Node.h"
namespace rut::cip
{
	template <typename T>
	class BaseBinaryTree
	{
	private:
		void InOrderRemoveTree(Node<T>* current);
		void InOrder(Node<T>* current);
		std::vector<T> values;
		void MakeValues();
	protected:
		Node<T>* root;
		Node<T>* left;
		Node<T>* right;
		size_t size;
		void Transplant(Node<T>* parent, Node<T>* son);
		Node<T>* TreeMin(Node<T> node);
		Node<T>* TreeMax(Node<T> node);
		void Swap(BaseBinaryTree<T>& other) noexcept;
		virtual Node<T>* Insert(Node<T>* current, Node<T>* node, Node<T>* parent);
		Node<T>* Find(Node<T>* current, const T& target) const noexcept;
	public:
		BaseBinaryTree();
		BaseBinaryTree(std::initializer_list<T> list);
		BaseBinaryTree(const BaseBinaryTree<T>& other);
		BaseBinaryTree(BaseBinaryTree<T>&& other) noexcept;
		BaseBinaryTree& operator=(const BaseBinaryTree<T>& other);
		BaseBinaryTree& operator=(BaseBinaryTree<T>&& other) noexcept;
		virtual ~BaseBinaryTree();
		bool Add(const T& value);
		bool Remove(const T& value);
		bool HasValue(const T& value) const noexcept;
		bool IsEmpty() const noexcept;
		size_t GetSize() const noexcept;
		std::string InOrderPrint() const noexcept;
	};

	template<typename T>
	inline void BaseBinaryTree<T>::InOrderRemoveTree(Node<T>* current)
	{
		if (nullptr == current)
		{
			return;
		}

		--this->size;
		this->InOrderRemoveTree(current->left);
		this->InOrderRemoveTree(current->right);

		delete current;
		current = nullptr;
	}

	template<typename T>
	inline void BaseBinaryTree<T>::InOrder(Node<T>* current)
	{
		if (nullptr == current)
		{
			return;
		}

		this->InOrder(current->left);
		this->values.push_back(current->data);
		this->InOrder(current->right);
	}

	template<typename T>
	inline void BaseBinaryTree<T>::MakeValues()
	{
		this->values.clear();
		this->InOrder(this->root);
	}

	template<typename T>
	inline void BaseBinaryTree<T>::Transplant(Node<T>* parent, Node<T>* son)
	{
	}

	template<typename T>
	inline Node<T>* BaseBinaryTree<T>::TreeMin(Node<T> node)
	{
		while (nullptr != node->left)
		{
			node = node->left;
		}

		return node;
	}

	template<typename T>
	inline Node<T>* BaseBinaryTree<T>::TreeMax(Node<T> node)
	{
		while (nullptr != node->right)
		{
			node = node->right;
		}

		return node;
	}

	template<typename T>
	inline void BaseBinaryTree<T>::Swap(BaseBinaryTree<T>& other) noexcept
	{
		std::swap(this->root, other.root);
		std::swap(this->left, other.left);
		std::swap(this->right, other.right);
	}

	template<typename T>
	inline Node<T>* BaseBinaryTree<T>::Insert(Node<T>* current, Node<T>* node, Node<T>* parent)
	{
		if (nullptr == current)
		{
			current = node;
			current->parent = parent;
			return current;
		}

		if (*node < *current)
		{
			current->left = this->Insert(current->left, node, current);
		}
		else if (*node > *current)
		{
			current->right = this->Insert(current->right, node, current);
		}

		return current;
	}

	template<typename T>
	inline Node<T>* BaseBinaryTree<T>::Find(Node<T>* current, const T& target) const noexcept
	{
		if (nullptr == current)
		{
			return nullptr;
		}
		if (std::less<T>()(target, current->data))
		{
			return this->Find(current->left, target);
		}
		else if (std::greater<T>()(target, current->data))
		{
			return this->Find(current->right, target);
		}
		else
		{
			return current;
		}
	}

	template<typename T>
	inline BaseBinaryTree<T>::BaseBinaryTree()
		: root{nullptr}, left{nullptr}, right{nullptr}
	{
	}

	template<typename T>
	inline BaseBinaryTree<T>::BaseBinaryTree(std::initializer_list<T> list)
		: BaseBinaryTree()
	{
		for (auto& item : list)
		{
			this->Add(item);
		}
	}

	template<typename T>
	inline BaseBinaryTree<T>::BaseBinaryTree(const BaseBinaryTree<T>& other)
		: BaseBinaryTree()
	{
		for (auto& item : other)
		{
			this->Add(item);
		}
	}

	template<typename T>
	inline BaseBinaryTree<T>::BaseBinaryTree(BaseBinaryTree<T>&& other) noexcept
		: BaseBinaryTree()
	{
		*this = other;
	}

	template<typename T>
	inline BaseBinaryTree<T>& BaseBinaryTree<T>::operator=(const BaseBinaryTree<T>& other)
	{
		if (this != other)
		{
			BaseBinaryTree<T> temp(other);
			this->Swap(temp);
		}

		return *this;
	}

	template<typename T>
	inline BaseBinaryTree<T>& BaseBinaryTree<T>::operator=(BaseBinaryTree<T>&& other) noexcept
	{
		if (this != other)
		{
			this->Swap(other);
		}

		return *this;
	}

	template<typename T>
	inline BaseBinaryTree<T>::~BaseBinaryTree()
	{
		this->InOrderRemoveTree(this->root);
		this->root = nullptr;
	}

	template<typename T>
	inline bool BaseBinaryTree<T>::Add(const T& value)
	{
		auto newNode = new Node<T>(value);
		if (nullptr == this->root)
		{
			this->root = newNode;
		}
		else
		{
			this->root = this->Insert(this->root, newNode, this->root->parent);
		}

		++this->size;
		this->MakeValues();
		return true;
	}

	template<typename T>
	inline bool BaseBinaryTree<T>::Remove(const T& value)
	{
		return false;
	}

	template<typename T>
	inline bool BaseBinaryTree<T>::HasValue(const T& value) const noexcept
	{
		return nullptr != this->Find(this->root, value);
	}

	template<typename T>
	inline bool BaseBinaryTree<T>::IsEmpty() const noexcept
	{
		return nullptr == this->root;
	}

	template<typename T>
	inline size_t BaseBinaryTree<T>::GetSize() const noexcept
	{
		return this->size;
	}

	template<typename T>
	inline std::string BaseBinaryTree<T>::InOrderPrint() const noexcept
	{
		std::ostringstream buffer{};
		buffer << "{ ";
		for (auto it = this->values.cbegin(); it != this->values.cend(); ++it)
		{
			buffer << (*it) << " ";
		}
		buffer << "}";

		return buffer.str();
	}

}