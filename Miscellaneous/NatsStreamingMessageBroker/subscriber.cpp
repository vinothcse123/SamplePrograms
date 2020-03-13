#include <nats.h>
#include <iostream>
#include <string.h>

natsStatus handleError(natsStatus &natsStat)
{
    std::cout << "Failure!!! Error Message: " << natsStatus_GetText(natsStat) << std::endl;
    nats_PrintLastErrorStack(stderr);
    return natsStat;
}

static void subscriberCallBack(stanConnection *sc, stanSubscription *sub, const char *channel, stanMsg *msg, void *closure)
{
    printf("Received on [%s]: sequence:%" PRIu64 " data:%.*s timestamp:%" PRId64 " redelivered: %s\n",
           channel,
           stanMsg_GetSequence(msg),
           stanMsg_GetDataLength(msg),
           stanMsg_GetData(msg),
           stanMsg_GetTimestamp(msg),
           stanMsg_IsRedelivered(msg) ? "yes" : "no");

    stanMsg_Destroy(msg);
}

natsStatus createNatsOptions(natsOptions *&natsOpts)
{
    natsStatus natsStat = NATS_OK;
    natsStat = natsOptions_Create(&natsOpts);
    if (natsStat != NATS_OK)
        return handleError(natsStat);

    const char *serverUrls[1];
    serverUrls[0] = NATS_DEFAULT_URL;
    natsStat = natsOptions_SetServers(natsOpts, serverUrls, 1);
    if (natsStat != NATS_OK)
        return handleError(natsStat);

    return natsStat;
}

natsStatus createStanNatsOptions(stanConnOptions *&stanConnOpts, natsOptions *&natsOpts)
{
    natsStatus natsStat = NATS_OK;
    natsStat = stanConnOptions_Create(&stanConnOpts);
    if (natsStat != NATS_OK)
        return handleError(natsStat);

    natsStat = stanConnOptions_SetNATSOptions(stanConnOpts, natsOpts);
    if (natsStat != NATS_OK)
        return handleError(natsStat);

    return natsStat;
}

natsStatus createStanSubOptions(stanSubOptions *&stanSubOpts)
{
    natsStatus natsStat = NATS_OK;
    natsStat = stanSubOptions_Create(&stanSubOpts);
    if (natsStat != NATS_OK)
        return handleError(natsStat);

    return natsStat;
}

natsStatus connectStreamingNats(stanConnection *&stanConn, stanConnOptions *&stanConnOpts)
{
    natsStatus natsStat = NATS_OK;
    natsStat = stanConnection_Connect(&stanConn, "test-cluster", "V6ClientIdSubcriber1", stanConnOpts);

    if (natsStat == NATS_OK)
        std::cout << "NATS Connection is successful!!!" << std::endl;
    else
        return handleError(natsStat);

    return natsStat;
}

natsStatus subscribeMessage(stanConnection *&stanConn, stanSubOptions *&stanSubOpts)
{
    natsStatus natsStat = NATS_OK;
    stanSubscription *stanSubscription = NULL;

    natsStat = stanConnection_Subscribe(&stanSubscription, stanConn, "VinothSubject", subscriberCallBack, NULL, stanSubOpts);

    if (natsStat != NATS_OK)
        return handleError(natsStat);

    return natsStat;
}

natsStatus natsDestroy(stanConnection *stanConn, stanConnOptions *stanConnOpts, natsOptions *natsOpts, stanSubOptions *stanSubOpts)
{
    natsOptions_Destroy(natsOpts);
    stanConnOptions_Destroy(stanConnOpts);
    stanConnection_Destroy(stanConn);
    stanSubOptions_Destroy(stanSubOpts);
    nats_Close();
}

int main()
{
    natsStatus natsStat;
    stanConnOptions *stanConnOpts = NULL;
    stanConnection *stanConn = NULL;
    natsOptions *natsOpts = NULL;
    stanSubOptions *stanSubOpts = NULL;

    /* setting nats/streaming nats options */
    if ((natsStat = createNatsOptions(natsOpts)) != NATS_OK)
        return natsStat;
    if ((natsStat = createStanNatsOptions(stanConnOpts, natsOpts)) != NATS_OK)
        return natsStat;
    if ((natsStat = createStanSubOptions(stanSubOpts)) != NATS_OK)
        return natsStat;

    /* connecting nats streaming server */
    if ((natsStat = connectStreamingNats(stanConn, stanConnOpts)) != NATS_OK)
        return natsStat;

    if ((natsStat = subscribeMessage(stanConn, stanSubOpts)) != NATS_OK)
        return natsStat;

    while (true)
        continue; // Wait for order!!!

    natsDestroy(stanConn, stanConnOpts, natsOpts, stanSubOpts);
    return 0;
}
