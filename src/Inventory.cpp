#include "Inventory.h"

void Inventory::AddItem(Item* _item)
{
	currentItem = AddNode(_item);
	_item->SetInventory(this);

}

void Inventory::nextItem()
{
	if (!currentItem)
	{
		currentItem = head;
	}
	//todavia hay items en la lista
	if (currentItem->next)
	{
		currentItem = currentItem->next;
	}
	else //ya llegamos a la cola, regresamos al head
	{
		currentItem = head;
	}
}

void Inventory::prevItem()
{
	if (!currentItem)
	{
		currentItem = tail;
	}

	else if (currentItem->prev)
	{
		currentItem = currentItem->prev;
	}
	else 
	{
		currentItem = tail;
	}


}

void Inventory::debugPrintContents()
{
	//iterar en la lista
	LLNode<Item>* iter = head;
	std::cout << "Item en inventario: " << std::endl;
	while (iter != nullptr)
	{
		std::cout << "\t" << iter->data->name << std::endl;
		iter = iter->next;
	}
}
