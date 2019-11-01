#include <catch.hpp>
#include "LinkedQueue.h"

TEST_CASE("Linked Queue", "[singly-linked list][queue][generic data]") {
  int data = 10;
  int *p_data = &data;
  size_t mem_size = sizeof(data);
  size_t capacity = 5;
  LQueue q;

  WHEN( "initializing" ) {
    Initialize(&q, capacity, mem_size);
    THEN( "the mem_size and capacity is constructed" ) {
      REQUIRE( q.mem_size == mem_size );
      REQUIRE( q.capacity == capacity );
      REQUIRE( q.queue_size == 0 );
      REQUIRE( q.head == NULL );
      REQUIRE( q.tail == NULL );
    }
  }

  SECTION( "enqueue" ) {
    for (int i = 0; i < q.capacity + 3; ++i) {
      Enqueue(&q, p_data);
      ++(*p_data);
      REQUIRE( *((int *)q.tail->data) == *p_data - 1 );
    }
  }
  SECTION( "dequeue" ) {
  }
}

