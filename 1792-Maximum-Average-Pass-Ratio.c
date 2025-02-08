double maxAverageRatio(int** classes, int classesSize, int* classesColSize, int extraStudents) {
    struct class {
        double delta;
        int id;
    };

    int pais(int n) {
        return (n - 1) / 2;
    }

    int lfilho(int n) {
        return 2*n + 1;
    }

    int rfilho(int n) {
        return 2*n + 2;
    }

    void add_class(struct class** heap, struct class* class, int id) {
        heap[id] = class;
        struct class* tmp;
        
        while(heap[pais(id)]->delta < heap[id]->delta) { 
            tmp = heap[pais(id)];
            heap[pais(id)] = heap[id];
            heap[id] = tmp;
            id = pais(id);
        }
    }

    void update_head(struct class** heap, int heap_size, double new_delta) {
        heap[0]->delta = new_delta;
        int id = 0;
        int m;
        struct class* tmp;
        while(true) {
            if(lfilho(id)>=heap_size && rfilho(id)>=heap_size) return;
            else if(rfilho(id)>=heap_size) m = lfilho(id);
            else m = heap[lfilho(id)]->delta > heap[rfilho(id)]->delta ? lfilho(id) : rfilho(id);

            if(heap[id]->delta < heap[m]->delta) {
                tmp = heap[id];
                heap[id] = heap[m];
                heap[m] = tmp;
                id = m;
            }
            else return;
        }
    }

    double cal_delta(int p, int t) {
        return (t - p) / (double)(t*(double)(t) + t);
    }

    double cal_ratio(int p, int t) {
        return p / (double)t;
    }

    void print_heap(struct class** heap, int heapSize) {
        int space = 1;

        for(int i = 0; i < heapSize; i++) {
            if(i>=space) {
                printf("\n");
                space = 2*space + space;
            }
            printf("%f ", heap[i]->delta);
        }
        printf("\n");
    }

    if(classesSize == 1) return (classes[0][0] + extraStudents) / (double)(classes[0][1] + extraStudents);

    double delta;
    struct class** maxHeap = malloc(sizeof(struct class*) * classesSize);
    struct class* tmp;

    for(int i = 0; i < classesSize; i++) {
        tmp = malloc(sizeof(struct class));
        tmp->delta = cal_delta(classes[i][0], classes[i][1]);
        tmp->id = i;
        add_class(maxHeap, tmp, i);
    }

    int id;

    while(extraStudents > 0) {
        id = maxHeap[0]->id;
        classes[id][0]++;
        classes[id][1]++;
        update_head(maxHeap, classesSize, cal_delta(classes[id][0], classes[id][1]));
        extraStudents--;
    }

    double avarage = 0.0;

    for(int i = 0; i < classesSize; i++) {
        avarage += (classes[i][0] / (double)(classes[i][1])) / (double)(classesSize);
    }

    free(maxHeap);
    return avarage;
}