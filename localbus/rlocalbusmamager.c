

//Main thread
// recv client connect put it in poll (no idea whether it is a pub or sub)
// when poll wakes up get the data create identify thread with the waked socket and move on


//Identity thread
// call recv syscall on the revieved socket
// once recv store the topic in malloced buf
// memcpy buffer in to "pubSubData_t"
// Check the "PUBSUB_DATA_TYPE_*"
// if "PUBSUB_DATA_TYPE_PUB_*",  create Publish Topic Thread
// if "PUBSUB_DATA_TYPE_SUBUB_*" create Subscribe Topic Thread
// exit the identity thread
//===== Dynamic Thread Creation ==== 


//Publish a topic thread
// call recv syscall on the revieved socket
// once recv store the topic in malloced buf
// send a reply to publisher
// read topic id and go to the "rPubSubTopicRecord" with topic as index
// aquire the "topicDb" mutex
// add the "topic" to  the end on the list
// release the mutex
// exit from the thread
//===== Dynamic Thread Creation ====

//Subscribe a topic
// call recv syscall on the revieved socket
// once recv store the topic in malloced buf
// send a reply to subscriber with replay type RRG_SUB
// read the topic id and go to the "rPubSubSubscriberRecord" with topic as index
// aquire record mutex
// add the socket info in list
// release mitex
// exit from thread
//===== Dynamic Thread Creation ====

//Subscriber Service thread
// get signalled by the publish thread
// browse through "rPubSubSubscriberRecord" "topic" by "topic"
// process one topic from the tail end move to next topic and come back again till there is no topic left
//Process
// take one topic
// take mutex of the topic list, so that no topic addition in topic list till process
// take the original topic pointer to a local pointer
// release mutex so that publisher can enqueue
// Browse Subscriber record by indexing "rPubSubSubscriberRecord" with topicId
// Thake the  Subscriber record mutex so that no subscriber can be added till we send the current topic to all current subscriber
// browse "subscriberDb" and send the Topic to all participant
// free the local topic pointer
// if any send fail Log it
//===== Its a static thread waiting on condition, which is signaled by Publisher thread ====

