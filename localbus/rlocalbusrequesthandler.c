


rPubSubStatus_t rPubSubRequestHandler(int fd, char *reqBuf, int bufLen)
{
    int i;
    rPubSubPublisherData_t *req = NULL;
    if (!reqBuf || bufLen == 0)
        return RPUBSUB_ERROR;
    req = (rPubSubPublisherData_t *)reqBuf;
    switch (req->reqRespType) {
        case PUBSUB_REQRESP_TYPE_PUB_REQ_TOPIC_ENQUEUE:
            {

            }
            break;
        case PUBSUB_REQRESP_TYPE_SUB_REQ_REGISTER :
            {

            }
            break;
        case PUBSUB_REQRESP_TYPE_SUB_REQ_DEREGISTER:
            {

            }
            break;
        case PUBSUB_REQRESP_TYPE_CLI_REQ_DBG:
            {

            }
            break;
        default:
            CONSOLE_PRINT("Unknown REQRESP_TYPE %d\n", req->reqRespType);
    }

    return RPUBSUB_SUCCESS;
}

rPubSubStatus_t rPubSubHandlePublisherReq(int fd, char *reqBuf, int bufLen)
{
    int i;
    rPubSubStatus_t ret;
    rPubSubPublisherData_t *req = NULL;
    rPubSubPublisherData_t *pubData = NULL;
    if (!reqBuf || bufLen == 0)
        return RPUBSUB_ERROR;
    req = (rPbuSubReqResp_t *)reqBuf;
    switch (req->reqRespType) {
        case PUBSUB_REQRESP_TYPE_PUB_REQ_TOPIC_ENQUEUE:
            {
                DBG_PRINT("Recieved Publish Request [fd %d,reqLen %d]\n", fd, bufLen);
                pubData = (rPubSubPublisherData_t *) malloc(bufLen);
                memcpy(pubData, reqBuf, bufLen);
                ret = rPubSubHandlePublisherTopicEnqueue(pubData);
                if (ret != RPUBSUB_SUCCESS) {
                    DBG_PRINT("Publish Request [fd %d,reqLen %d] - Enqueue Fail\n", fd, bufLen);
                    return RPUBSUB_FAIL;
                }
                ret = rPubSubSendPublisherResp(fd, reqBuf, bufLen);
                if (ret != RPUBSUB_SUCCESS) {
                    DBG_PRINT("Publish Send Response [fd %d,reqLen %d] - Fail\n", fd, bufLen);
                    return RPUBSUB_FAIL;
                }
                return RPUBSUB_SUCCESS;
            }
            break;
        case PUBSUB_REQRESP_TYPE_PUB_REQ_TOPIC_ENQUEUE_ROLLBACK:
            {
                DBG_PRINT("Recieved Publish Rollback Request [fd %d,reqLen %d]\n", fd, bufLen);

            }
            break;
        default:
            CONSOLE_PRINT("Unknown Publisher REQRESP_TYPE %d\n", req->reqRespType);
            break;
    }

    return RPUBSUB_SUCCESS;
}

rPubSubStatus_t rPubSubHandleSubscriberReq(int fd, char *reqBuf, int bufLen)
{
    int i;
    if (!reqBuf || bufLen == 0)
        return RPUBSUB_ERROR;
    req = (rPbuSubReqResp_t *)reqBuf;
    switch (req->reqRespType) {
        case PUBSUB_REQRESP_TYPE_SUB_REQ_REGISTER:
            {
                DBG_PRINT("Recieved Subscription Request [fd %d,reqLen %d]\n", fd, bufLen);

            }
            break;
        case PUBSUB_REQRESP_TYPE_SUB_REQ_DEREGISTER:
            {
                DBG_PRINT("Recieved Un-Subscription Request [fd %d,reqLen %d]\n", fd, bufLen);

            }
            break;
        default:
            CONSOLE_PRINT("Unknown Subscriber REQRESP_TYPE %d\n", req->reqRespType);
            break;
    }

    return RPUBSUB_SUCCESS;
}

rPubSubStatus_t rPubSubHandleCliReq(int fd, char *reqBuf, int bufLen)
{
    int i;
    if (!reqBuf || bufLen == 0)
        return RPUBSUB_ERROR;
    req = (rPbuSubReqResp_t *)reqBuf;
    switch (req->reqRespType) {
        case PUBSUB_REQRESP_TYPE_CLI_REQ_DBG:
            {
                DBG_PRINT("Recieved Cli Request [fd %d,reqLen %d]\n", fd, bufLen);
            }
            break;
        default:
            CONSOLE_PRINT("Unknown Cli REQRESP_TYPE %d\n", req->reqRespType);
            break;
    }

    return RPUBSUB_SUCCESS;
}





