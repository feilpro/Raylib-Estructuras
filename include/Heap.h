#pragma once
#include <iostream>
#include <vector>
#include "raylib.h"
using namespace std;



struct Footprint {
	Vector2 position;
	int priority;
};


class Heap
{
private:
	//Array o vector para almacenar elementos
	vector<Footprint> heap;


public:
	//Insert
	void insert(Vector2 pos, int priority)
	{
		heap.push_back({ pos, priority });
	}

	//Extract
	Footprint extractMin()
	{
		if (heap.empty()) return { {0, 0}, -1 };
		Footprint minFootprint = heap[0];
		heap[0] = heap.back();
		heap.pop_back();
		heapifyDown(0);
		return minFootprint;
	}

	void heapifyDown(int index)
	{
		int left = 2 * index + 1;
		int right = 2 * index + 2;
		int smallest = index;

		if (left < heap.size() && heap[left].priority < heap[smallest].priority)
			smallest = left;
		if (right < heap.size() && heap[right].priority < heap[smallest].priority)
			smallest = right;

		if (smallest != index) {
			swap(heap[index], heap[smallest]);
			heapifyDown(smallest);
		}
	}

	//Peek
	Footprint peek() {
		if (heap.empty()) return { {0, 0}, -1 };
		return heap[0];
	}

	//Is Empty
	bool is_empty()
	{
		return heap.empty();
	}

	void drawFootprints(Vector2 position, Texture2D texture) {
		for (auto& footprint : heap) {
			//DrawCircle((footprint.position.x + 17), (footprint.position.y + 36), 5, GRAY);
			DrawTexture(texture, (footprint.position.x + 6), (footprint.position.y + 21), WHITE);
		}
	}

	void removeOldFootprints(float maxAge) {
		while (!heap.empty() && (GetTime() - heap[0].priority > maxAge)) {
			heap.erase(heap.begin());
		}
	}

};
