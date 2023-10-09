#pragma once
namespace rut::cip 
{
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
		~Node() = default;
		friend auto operator<=>(const Node& lha, const Node& rha);
		friend bool operator==(const Node& lha, const Node& rha);
	};
}