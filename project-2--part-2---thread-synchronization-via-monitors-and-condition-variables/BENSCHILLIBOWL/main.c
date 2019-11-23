#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "BENSCHILLIBOWL.h"

// Feel free to play with these numbers! This is a great way to
// test your implementation.
#define BENSCHILLIBOWL_SIZE 100
#define NUM_CUSTOMERS 10
#define NUM_COOKS 5
#define ORDERS_PER_CUSTOMER 10
#define EXPECTED_NUM_ORDERS NUM_CUSTOMERS * ORDERS_PER_CUSTOMER

// Global variable for the restaurant.
BENSCHILLIBOWL *bcb;

/**
 * Thread funtion that represents a customer. A customer should:
 *  - allocate space (memory) for an order.
 *  - select a menu item.
 *  - populate the order with their menu item and their customer ID.
 *  - add their order to the restaurant.
 */
void* BENSCHILLIBOWLCustomer(void* tid) {
    int customer_id = (int)(long) tid;
    Order *o = malloc(sizeof(Order));
    o->menu_item = PickRandomMenuItem();
    o->customer_id = customer_id;
    AddOrder(bcb,o);
    return NULL;
}

/**
 * Thread function that represents a cook in the restaurant. A cook should:
 *  - get an order from the restaurant.
 *  - if the order is valid, it should fulfill the order, and then
 *    free the space taken by the order.
 * The cook should take orders from the restaurants until it does not
 * receive an order.
 */
void* BENSCHILLIBOWLCook(void* tid) {
  int cook_id = (int)(long) tid;
	int orders_fulfilled = 0;
  Order *o = GetOrder(bcb);
  if (bcb->current_size < bcb->max_size){
    sleep(1); //wait for order to be fulfilled
    printf("Cook #%d fulfilled %d orders\n", cook_id, orders_fulfilled++);
    free(o);
  }
	return NULL;
}

/**
 * Runs when the program begins executing. This program should:
 *  - open the restaurant
 *  - create customers and cooks
 *  - wait for all customers and cooks to be done
 *  - close the restaurant.
 */
int main() {
   //Open the restaurant
    BENSCHILLIBOWL *bcb = malloc(sizeof(BENSCHILLIBOWL));
  
  //Create customers and cooks 
   pthreadt_t customer_thread[NUM_CUSTOMERS];
   pthreadt_t cook_thread[NUM_COOKS];
  
   for(int i = 0; i < NUM_CUSTOMERS; i++){
     pthread_create(&customer_thread,NULL,BENSCHILLIBOWLCustomer, customer_thread);
   }
    
   for(int i = 0; i < NUM_COOKS; i++){
     pthread_create(&cook_thread,NULL,BENSCHILLIBOWLCook,cook_thread);
   }
  
  //Wait for customers and cooks to be done
  for(int i = 0; i < NUM_CUSTOMERS; i++){
    pthread_join(customer_thread[i], NULL);
  }
	for(int i = 0; i < NUM_COOKS; i++){
    pthread_join(cook_thread[i], NULL);
  }
   //Close the restaurant
   free(bcb);
    return 0;
}