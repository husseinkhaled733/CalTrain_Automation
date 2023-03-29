#include <pthread.h>

struct station {
    pthread_mutex_t mutex;
    pthread_cond_t train_arrived;
    pthread_cond_t passengers_seated;
    int waiting_passengers;
    int enough_seats;
    int free_seats_on_train;
    // FILL ME IN
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);