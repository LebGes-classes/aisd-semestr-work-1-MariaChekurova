
#include <iostream>
#include "SegmentTreeProject.h"
using namespace std;

SegmentTree::SegmentTree(std::vector<int> array) : startArray(array)
{
	size = (int) startArray.size();
	create(array);
}

void SegmentTree::create(std::vector<int> array)
{
	minTree.resize(size * 4);
	maxTree.resize(size * 4);
	sumTree.resize(size * 4);
	for (int i = 0; i < size; i++)	// заполнение листьев
	{
		sumTree[i + size] = array[i];
		minTree[i + size] = array[i];
		maxTree[i + size] = array[i];
	}
	for (int i = size - 1; i > 0; i--)	// заполнение оставшихся элементов
	{
		sumTree[i] = sumTree[2 * i + 1] + sumTree[2 * i];
		minTree[i] = std::min(minTree[2 * i + 1], minTree[2 * i]);
		maxTree[i] = std::max(maxTree[2 * i + 1], maxTree[2 * i]);
	}
}


int SegmentTree::getMin(int leftIndex, int rightIndex)
{
	int min = 2 ^ 32;
	leftIndex += size;
	rightIndex += size;

	while (leftIndex <= rightIndex)
	{
		if (leftIndex % 2 != 0) //если левый элемент - правый ребенок, то сравниваем ответ с этим элементом, так как отрезок, который покрывает родитель данного элемента, будет выходить за пределы заданного отрезка, а значит с родителем сравнивать не нужно
		{
			min = std::min(minTree[leftIndex], min);
		}
		if (rightIndex % 2 == 0) //если правый элемент - левый ребенок, то сравниваем ответ с этим элементом, так как отрезок, который покрывает родитель данного элемента, будет выходить за пределы заданного отрезка, а значит с родителем сравнивать не нужно
		{
			min = std::min(minTree[rightIndex], min);
		}											// в общем случае проходим от детей к родителям
		leftIndex = (leftIndex + 1) / 2; // продвигаемся по дереву вверх и вправо (вверх - чтобы увидеть родителя и добавить его в сумму, если нужно; вправо - чтобы проверять, нужно ли прибавлять к сумме текущий элемент)
		rightIndex = (rightIndex - 1) / 2; // продвигаемся по дереву вверх и влево (вверх - увидеть родителя текущего элемента, влево - проверить, нужно ли прибавлять к сумме текущий элемент)
	}									   // изменяем левый и правый индексы, чтобы найти родителя, который охватывает максимальную часть введенного отрезка (поэтому двигвем левый и правый индексы друг к другу)
	return min;
}

int SegmentTree::getMax(int leftIndex, int rightIndex)
{
	int max = 0;
	leftIndex += size;
	rightIndex += size;

	while (leftIndex <= rightIndex)
	{
		if (leftIndex % 2 != 0) //если левый элемент - правый ребенок, то сравниваем ответ с этим элементом, так как отрезок, который покрывает родитель данного элемента, будет выходить за пределы заданного отрезка, а значит с родителем сравнивать не нужно
		{	
			max = std::max(maxTree[leftIndex], max); 
		}
		if (rightIndex % 2 == 0) //если правый элемент - левый ребенок, то сравниваем ответ с этим элементом, так как отрезок, который покрывает родитель данного элемента, будет выходить за пределы заданного отрезка, а значит с родителем сравнивать не нужно
		{
			max = std::max(maxTree[rightIndex], max);
		}								// в общем случае проходим от детей к родителям
		leftIndex = (leftIndex + 1) / 2; // продвигаемся по дереву вверх и вправо
		rightIndex = (rightIndex - 1) / 2; // продвигаемся по дереву вверх и влево
	}									   // изменяем левый и правый индексы, чтобы найти родителя, который охватывает максимальную часть введенного отрезка (поэтому двигвем левый и правый индексы друг к другу)
	return max;
}

int SegmentTree::getSum(int leftIndex, int rightIndex)
{
	int sum = 0;
	leftIndex += size;
	rightIndex += size;

	while (leftIndex <= rightIndex)
	{
		if (leftIndex % 2 != 0) //если левый элемент - правый ребенок, то увеличиваем ответ на этот элемент, так как отрезок, который покрывает родитель данного элемента, будет выходить за пределы заданного отрезка, а значит родителя брать не нужно
		{
			sum += sumTree[leftIndex]; 
		}
		if (rightIndex % 2 == 0) //если правый элемент - левый ребенок, то увеличиваем ответ на этот элемент, так как отрезок, который покрывает родитель данного элемента, будет выходить за пределы заданного отрезка, а значит родителя брать не нужно
		{
			sum += sumTree[rightIndex]; 
		}								// в общем случае проходим от детей к родителям
		leftIndex = (leftIndex + 1) / 2; // продвигаемся по дереву вверх и вправо (вверх - чтобы увидеть родителя и добавить его в сумму, если нужно; вправо - чтобы проверять, нужно ли прибавлять к сумме текущий элемент)
		rightIndex = (rightIndex - 1) / 2; // продвигаемся по дереву вверх и влево (вверх - увидеть родителя текущего элемента, влево - проверить, нужно ли прибавлять к сумме текущий элемент)
	}									   // изменяем левый и правый индексы, чтобы найти родителя, который охватывает максимальную часть введенного отрезка (поэтому двигвем левый и правый индексы друг к другу)
	return sum;
}

void SegmentTree::update(int index, int value)
{
	index = index + size;		// ищем индекс в дереве
	sumTree[index] = value; 
	minTree[index] = value;
	maxTree[index] = value;

	while (index > 0)			// циклом проходим по родителям измененного элемента и изменяем их, если нужно
	{
		if (index % 2 == 0)		// если текущий элемент - левый ребенок, то изменяем родителя, найдя правого ребенка того же родителя по формуле index + 1
		{
			sumTree[index / 2] = sumTree[index] + sumTree[index + 1];
			minTree[index / 2] = std::min( minTree[index], minTree[index + 1] );
			maxTree[index / 2] = std::max( maxTree[index], maxTree[index + 1] );
		}
		if (index % 2 != 0)		// если текущий элемент - правый ребенок, то изменяем родителя, найдя левого ребенка того же родителя по формуле index - 1
		{
			sumTree[index / 2] = sumTree[index-1] + sumTree[index];
			minTree[index / 2] = std::min(minTree[index-1], minTree[index]);
			maxTree[index / 2] = std::max(maxTree[index-1], maxTree[index]);
		}
		index = index / 2;
	}
}

void SegmentTree::remove(int index)
{
	startArray.erase(startArray.begin() + index);		// изменяем стартовый массив
	size--;
	create(startArray);		// перезапись дерева
}

void SegmentTree::add(int value)
{
	startArray.push_back(value);		// изменяем стартовый массив
	size++;
	create(startArray);		// перезапись дерева
}

void SegmentTree::add(int index, int value)
{
	startArray.insert(startArray.begin() + index, value);		// изменяем стартовый массив
	size++;
	create(startArray);		// перезапись дерева
}
