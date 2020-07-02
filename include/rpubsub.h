#include <stdio.h>
#include <stdlib.h>
#ifndef __RPUBSUB_H__
#define __RPUBSUB_H__

#define MAX_NAME_LEN   70
#define MAX_TOPIC               70
#define MAX_SUBSCRIBER_THREAD   MAX_TOPIC 

/* TOPIC */

/**/
typedef enum {
         PUBSUB_DATA_TYPE_PUB_REQ_TOPIC_ENQUEUE,
         PUBSUB_DATA_TYPE_PUB_RESP_TOPIC_ENQUEUE_PASS,
         PUBSUB_DATA_TYPE_PUB_RESP_TOPIC_ENQUEUE_FAIL,
         PUBSUB_DATA_TYPE_PUB_REQ_TOPIC_ENQUEUE_ROLLBACK,
         PUBSUB_DATA_TYPE_PUB_RESP_TOPIC_ENQUEUE_ROLLBACK_PASS,
         PUBSUB_DATA_TYPE_PUB_RESP_TOPIC_ENQUEUE_ROLLBACK_FAIL,
         PUBSUB_DATA_TYPE_SUB_REQ_REGISTER,
         PUBSUB_DATA_TYPE_SUB_RESP_REGISTER_PASS,
         PUBSUB_DATA_TYPE_SUB_RESP_REGISTER_FAIL,
         PUBSUB_DATA_TYPE_SUB_REQ_DEREGISTER,
         PUBSUB_DATA_TYPE_SUB_RESP_DEREGISTER_PASS,
         PUBSUB_DATA_TYPE_SUB_RESP_DEREGISTER_FAIL,
         PUBSUB_DATA_TYPE_SUB_REQ_RESP_MAX
}pubSubDataType_t;

/**/
typedef struct pubSubData_s{
         pubSubDataType_t dataType;
         rPubSubTopic_t *topic;
}pubSubData_t;

/**/
typedef struct rPubSubBusContext_s {
        struct sockaddr_in busAddr;
}rPubSubBusContext_t;

/**/
typedef struct rPubSubBus_s {
        int socket;
}rPubSubBus_t;

/**/
typedef struct _rPubSubSubscriber_s {
    int SubscriberId;
    char SubscriberName[MAX_NAME_LEN];
    rPubSubBus_t *rPubSubBus;
    int maxSubscription;
    int maxTopic;
    int currTopicCount;
    int currSubscribedTopic[MAX_TOPIC][MAX_SUBSCRIBER_THREAD];
    struct _rPubSubSubscriber_s *next;
}rPubSubSubscriber_t;

/**/
rPubSubBus_t    *rPubSubBusConnect(rPubSubBusContext_t *rPubSubBus);
rPubSubStatus_t *rPubSubPublish(rPubSubBus_t *rPubSubBus, rPubSubTopic_t *topic);

rPubSubSubscriber_t *rPubSubSubBusSubscriberCreate(rPubSubBusContext_t *rPubSubBus);
rPubSubSubscribe_t *rPubSubSubBusSubscriberDestroy(rPubSubSubscriber_t *subscriber);

rPubSubStatus_t *rPubSubSubscribe(rPubSubSubscriber_t *rPubSubBusSubscriber, rPubSubTopic_t *topic,
                                     void (*callback) (rPubSubTopic_t *topic));
rPubSubStatus_t *rPubSubUnSubscribe(rPubSubSubscriber_t *rPubSubBusSubscriber, rPubSubTopic_t *topic);
#endif //__RPUBSUB_H__
