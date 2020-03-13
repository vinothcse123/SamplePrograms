#include <nats.h>
#include <iostream>
#include <string.h>

natsStatus handleError(natsStatus &natsStat)
{
    std::cout << "Failure!!! Error Message: " << natsStatus_GetText(natsStat) << std::endl;
    nats_PrintLastErrorStack(stderr);
    return natsStat;
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

natsStatus connectStreamingNats(stanConnection *&stanConn, stanConnOptions *&stanConnOpts)
{
    natsStatus natsStat = NATS_OK;
    natsStat = stanConnection_Connect(&stanConn, "test-cluster", "V6ClientIdPublisher1", stanConnOpts);

    if (natsStat == NATS_OK)
        std::cout << "NATS Connection is successful!!!" << std::endl;
    else
        return handleError(natsStat);

    return natsStat;
}

natsStatus publishMessage(stanConnection *&stanConn)
{
    natsStatus natsStat = NATS_OK;
    std::string pubString = "HAI I AM PUBLISHER...";
    natsStat = stanConnection_Publish(stanConn, "VinothSubject", pubString.c_str(), pubString.length());
    if (natsStat != NATS_OK)
        return handleError(natsStat);

    return natsStat;
}

natsStatus natsDestroy(stanConnection *stanConn, stanConnOptions *stanConnOpts, natsOptions *natsOpts)
{
    natsOptions_Destroy(natsOpts);
    stanConnOptions_Destroy(stanConnOpts);
    stanConnection_Destroy(stanConn);
    nats_Close();
}

int main()
{
    natsStatus natsStat;
    stanConnOptions *stanConnOpts = NULL;
    stanConnection *stanConn = NULL;
    natsOptions *natsOpts = NULL;

    /* setting nats/streaming nats options */
    if ((natsStat = createNatsOptions(natsOpts)) != NATS_OK)
        return natsStat;
    if ((natsStat = createStanNatsOptions(stanConnOpts, natsOpts)) != NATS_OK)
        return natsStat;

    /* connecting nats streaming server */
    if ((natsStat = connectStreamingNats(stanConn, stanConnOpts)) != NATS_OK)
        return natsStat;

    if ((natsStat = publishMessage(stanConn)) != NATS_OK)
        return natsStat;

    natsDestroy(stanConn, stanConnOpts, natsOpts);
    return 0;
}
