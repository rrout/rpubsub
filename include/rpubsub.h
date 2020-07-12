#include <stdio.h>
#include <stdlib.h>
#ifndef __RPUBSUB_H__
#define __RPUBSUB_H__

#define MAX_NAME_LEN   70
#define MAX_TOPIC               70
#define MAX_SUBSCRIBER_THREAD   MAX_TOPIC 

/* TOPIC */
typedef enum {
    RPUBSUB_TOPIC_DEBUG,
    RPUBSUB_TOPIC_LOW_DISK_SPACE,
    RPUBSUB_TOPIC_LOW_BATERY,
    RPUBSUB_TOPIC_MAX
}rPubSubTopicId_t;

typedef struct rPubSubTopic_s {
    rPubSubTopicId_t topicId;
    int topicLen;
    void topic[0];
}rPubSubTopic_t;

/**/
typedef enum {
         PUBSUB_REQRESP_TYPE_PUB_REQ_TOPIC_ENQUEUE,
         PUBSUB_REQRESP_TYPE_PUB_RESP_TOPIC_ENQUEUE_PASS,
         PUBSUB_REQRESP_TYPE_PUB_RESP_TOPIC_ENQUEUE_FAIL,
         PUBSUB_REQRESP_TYPE_PUB_REQ_TOPIC_ENQUEUE_ROLLBACK,
         PUBSUB_REQRESP_TYPE_PUB_RESP_TOPIC_ENQUEUE_ROLLBACK_PASS,
         PUBSUB_REQRESP_TYPE_PUB_RESP_TOPIC_ENQUEUE_ROLLBACK_FAIL,
         PUBSUB_REQRESP_TYPE_SUB_REQ_REGISTER,
         PUBSUB_REQRESP_TYPE_SUB_RESP_REGISTER_PASS,
         PUBSUB_REQRESP_TYPE_SUB_RESP_REGISTER_FAIL,
         PUBSUB_REQRESP_TYPE_SUB_REQ_DEREGISTER,
         PUBSUB_REQRESP_TYPE_SUB_RESP_DEREGISTER_PASS,
         PUBSUB_REQRESP_TYPE_SUB_RESP_DEREGISTER_FAIL,
         PUBSUB_REQRESP_TYPE_CLI_REQ_DBG,
         PUBSUB_REQRESP_TYPE_SUB_REQ_RESP_MAX
}rPubSubReqRespType_t;

/**/
typedef struct rPubSubPublisherData_s{
         rPubSubReqRespType_t reqRespType;
         rPubSubTopic_t *topic;
}rPubSubPublisherData_t;

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
