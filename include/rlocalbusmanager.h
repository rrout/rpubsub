

/* TOPIC DATA BASE */
typedef struct rPubSubTopicDb_s {
        int topicId;
        rPubSubTopic_t *topic;
        struct rPubSubTopicDb_s *next;
}rPubSubTopicDb_t;

typedef struct rPubSubTopicRecord_s {
        rPubSubTopicDb_t *topic;
        pthread_mutex_t subscriberDbLock; //per topic mutex which helps to add/remove topic to topic record Db
        rPubSubTopicDb_t *topicList;
}rPubSubTopicRecord_t;
/*
MAX_TOPIC
 |========|
0|lock, * |->|TOPIC|->|TOPIC|->|TOPIC|->
 |========|
 |lock, * |->|TOPIC|->|TOPIC|->|TOPIC|->
 |========|
 |lock, * |->|TOPIC|->|TOPIC|->|TOPIC|->
 |========|
 |lock, * |->|TOPIC|->|TOPIC|->|TOPIC|->
 |========|
 |lock, * |->|TOPIC|->|TOPIC|->|TOPIC|->
 |========|
 |        |
 |        |
 |        |
 |        |
 |========|
 |lock, * |->|TOPIC|->|TOPIC|->|TOPIC|->
 |========|
n|lock, * |->|TOPIC|->|TOPIC|->|TOPIC|->
 |========|
*/
extern rPubSubTopicRecord_t      rPubSubTopicRecord[MAX_TOPIC];


/* SUBSCRIBER DATABASE */
typedef struct rPubSubSubscriber_s {
        int topicId;
        int subSocket;
}rPubSubSubscriber_t;

typedef struct rPubSubSubscriberDb_s {
        rPubSubSubscriber_t subscriber;
        struct rPubSubSubscriberDb_s *next;
}rPubSubSubscriberDb_t;

typedef struct rPubSubSubscriberRecord_s {
        int listId;
        pthread_mutex_t subscriberDbLock;//per Subscriber mutex which helps to add/remove subscriber to record Db
        rPubSubSubscriberDb_t *list;
}rPubSubTopicRecord_t;

/*
MAX_TOPIC
 |========|
0|lock, * |->|SUBSCRIBER|->|SUBSCRIBER|->|SUBSCRIBER|->
 |========|
 |lock, * |->|SUBSCRIBER|->|SUBSCRIBER|->|SUBSCRIBER|->
 |========|
 |lock, * |->|SUBSCRIBER|->|SUBSCRIBER|->|SUBSCRIBER|->
 |========|
 |lock, * |->|SUBSCRIBER|->|SUBSCRIBER|->|SUBSCRIBER|->
 |========|
 |lock, * |->|SUBSCRIBER|->|SUBSCRIBER|->|SUBSCRIBER|->
 |========|
 |        |
 |        |
 |        |
 |        |
 |========|
 |lock, * |->|SUBSCRIBER|->|SUBSCRIBER|->|SUBSCRIBER|->
 |========|
n|lock, * |->|SUBSCRIBER|->|SUBSCRIBER|->|SUBSCRIBER|->
 |========|
*/
rPubSubSubscriberRecord_t rPubSubSubscriberRecord[MAX_TOPIC];

