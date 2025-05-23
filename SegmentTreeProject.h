#pragma once

#include <vector>

#ifndef SEGMENTTREE_H
#define SEGMENTTREE_H

class SegmentTree
{
	int size;
	std::vector<int> sumTree;
	std::vector<int> minTree;
	std::vector<int> maxTree;
	void create(std::vector<int> array); // построение дерева

public:
	std::vector<int> startArray;
	SegmentTree(std::vector<int> array);
	int getMin(int leftIndex, int rightIndex);		// получить минимальный элемент на отрезке [leftIndex, rightIndex
	int getMax(int leftIndex, int rightIndex);		// получить минимальный элемент на отрезке [leftIndex, rightIndex]
	int getSum(int leftIndex, int rightIndex);		// получить сумму элементов на отрезке [leftIndex, rightIndex]
	void update(int index, int value);				// заменить элемент исходного массива на позиции index на новое значение value
	void remove(int index);							// удалить элемент исходного массива на позиции index
	void add(int value);							// добавить элемент в конец исходного массива
	void add(int index, int value);					// добавить элемент на указанный индекс исходного массива

};

#endif

