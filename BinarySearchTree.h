#pragma once
#include <iostream>
#define __BST_DEBUG

template<typename T>
class BinarySearchTree
{
private:
	class Node
	{
		T value;
		Node* left;
		Node* right;
		Node(const T& value) : value(value), left(nullptr), right(nullptr) {}
		Node(T&& value) : value(std::move(value)), left(nullptr), right(nullptr) {}
		template<typename... Args>
		Node(Args&&... args) : value(std::forward<Args>(args)...), left(nullptr), right(nullptr) {}
		friend class BinarySearchTree;
	};

	Node* m_Root = nullptr;

public:
	void Insert(const T& value);
	void Insert(T&& value);
	template<typename... Args>
	void Emplace(Args&&... args);
	bool Contains(const T& value);
	void Remove(const T& value);
	void Cout();

private:
	Node* Insert(Node* currentNode, Node* keyNode);
	Node* Contains(Node* currentNode, const T& value);
	Node* MinNode(Node* node);
	Node* Remove(Node* root, const T& value);

	void Clear(Node* root);
	void Inorder(Node* node);

public:
	BinarySearchTree() : m_Root(nullptr) {};
	~BinarySearchTree();
};

template<typename T>
inline void BinarySearchTree<T>::Insert(const T& value)
{
	m_Root = Insert(m_Root, new Node(value));
}

template<typename T>
inline void BinarySearchTree<T>::Insert(T&& value)
{
	m_Root = Insert(m_Root, new Node(std::move(value)));
}

template<typename T>
inline bool BinarySearchTree<T>::Contains(const T& value)
{
	return Contains(m_Root, value) != nullptr;
}

template<typename T>
inline void BinarySearchTree<T>::Remove(const T& value)
{
	m_Root = Remove(m_Root, value);
}

template<typename T>
inline void BinarySearchTree<T>::Cout()
{
	Inorder(m_Root);
}

template<typename T>
inline typename BinarySearchTree<T>::Node* BinarySearchTree<T>::Insert(Node* currentNode, Node* keyNode)
{
	if (!currentNode) return keyNode;

	if (keyNode->value < currentNode->value)
		currentNode->left = Insert(currentNode->left, keyNode);
	else if (keyNode->value > currentNode->value)
		currentNode->right = Insert(currentNode->right, keyNode);
	else delete keyNode;
	
	return currentNode;
}

template<typename T>
inline typename BinarySearchTree<T>::Node* BinarySearchTree<T>::Contains(Node* currentNode, const T& value)
{
	if (!currentNode || currentNode->value == value)
		return currentNode;

	if (currentNode->value < value)
		return Contains(currentNode->right, value);

	return Contains(currentNode->left, value);
}

template<typename T>
inline typename BinarySearchTree<T>::Node* BinarySearchTree<T>::MinNode(Node* node)
{
	Node* current = node;
	while (current && current->left)
		current = current->left;
	return current;
}

template<typename T>
inline typename BinarySearchTree<T>::Node* BinarySearchTree<T>::Remove(Node* root, const T& value)
{
	if (!root) return root;

	if (value < root->value)
		root->left = Remove(root->left, value);
	else if (value > root->value)
		root->right = Remove(root->right, value);
	else
	{
		if (!root->left)
		{
			Node* temp = root->right;
			delete root;
			return temp;
		}
		else if (!root->right)
		{
			Node* temp = root->left;
			delete root;
			return temp;
		}

		Node* temp = MinNode(root->right);
		root->value = temp->value;
		root->right = Remove(root->right, temp->value);
	}

	return root;
}

template<typename T>
inline void BinarySearchTree<T>::Clear(Node* root)
{
	if (root)
	{
		Clear(root->right);
		Clear(root->left);
		delete root;
	}
}

template<typename T>
inline void BinarySearchTree<T>::Inorder(Node* node)
{
	if (node)
	{
		Inorder(node->left);
		std::cout << node->value << '\n';
		Inorder(node->right);
	}
}

template<typename T>
inline BinarySearchTree<T>::~BinarySearchTree()
{
	Clear(m_Root);
}

template<typename T>
template<typename ...Args>
inline void BinarySearchTree<T>::Emplace(Args && ...args)
{
	m_Root = Insert(m_Root, new Node(std::forward<Args>(args)...));
}
