#include "GameHistory.h"
#include "DeckManager.h"
#include <iostream>
#include <cstring>

void save(rec* &head){
	/*
	 * Function: Copy the save the current step
	 * Parameter: head of the pointer
	 */
	rec* new_node = new rec(operation_cards, head);
	head = new_node;
}

void undo(rec* &head){
	/*
	 * Function: Undo the step
	 * Patameter: head of the pointer
	 */

	// The case that there's no previous node
	if (head == nullptr || head->next == nullptr){
		std::cout << "Invalid operation, cannot move back" << std::endl;
		return;
	}

	// Return to the previous one
	memcpy(operation_cards, head->next->cards, sizeof(operation_cards));
    memcpy(remainingDeck, head->next->remainingDeck, sizeof(remainingDeck));
    remainingCount = head->next->remainingCount;
    completedSets = head->next->completedSets;
	rec* temp = head;
	head = head->next;
	delete temp;
}
