//
// Created by Calun on 2021/1/16.
//

#include "migong.h"
#include "../calunvier/tools.h"
#include "../objects/list.h"
#include <stdlib.h>

#define MAX_INT ((unsigned int)(-1)>>1)


typedef struct {
    ObjList header;
    int known;
    int dist;
    int path;
} DijkstraTable;


typedef struct {
    int x;
    int y;
    int distance;
    int index_in_table;
} MapVertex;


void initTable(DijkstraTable *table, void *graph, int vertex_number, int start, void (*readGraph)(void *, DijkstraTable *)) {
    int i;
    readGraph(graph, table);
    for (i = 0; i < vertex_number; i++) {
        table[i].dist = MAX_INT;
        table[i].known = 0;
        table[i].path = -1;
    }
    table[start].dist = 0;
}

MapVertex *transportIntegerMap2ObjMap(int (*_int_map)[]) {
    int i, j, (*int_map)[WEEK3_MIGONG_MIGONG_SIZE] = _int_map;
    MapVertex (*objMap)[WEEK3_MIGONG_MIGONG_SIZE] = malloc(
            sizeof(MapVertex) * WEEK3_MIGONG_MIGONG_SIZE * WEEK3_MIGONG_MIGONG_SIZE);
    for (i = 0; i < WEEK3_MIGONG_MIGONG_SIZE; ++i) {
        for (j = 0; j < WEEK3_MIGONG_MIGONG_SIZE; ++j) {
            objMap[i][j].x = i;
            objMap[i][j].y = j;
            objMap[i][j].distance = int_map[i][j];
            objMap[i][j].index_in_table = -1;
        }
    }
    return (MapVertex *) objMap;
}


void readGraphFromIntegerMap(void * _int_map, DijkstraTable *table) {
    int i, j, v = 0;
    MapVertex (*obj_map)[WEEK3_MIGONG_MIGONG_SIZE] = _int_map;
    ObjList temp_list;
    for (i = 0; i < WEEK3_MIGONG_MIGONG_SIZE; ++i) {
        for (j = 0; j < WEEK3_MIGONG_MIGONG_SIZE; ++j) {
            //Check if is 0
            if (obj_map[i][j].distance == 0) continue;
            else {
                table[v++].header = (temp_list = newObjList(sizeof(MapVertex)));
                ObjList_append(temp_list, &obj_map[i][j]);
                obj_map[i][j].index_in_table = v-1;
            }

            if (i - 1 > 0 && obj_map[i - 1][j].distance != 0) {
                // up
                ObjList_append(temp_list, &obj_map[i - 1][j]);
            }
            if (i + 1 < WEEK3_MIGONG_MIGONG_SIZE && obj_map[i + 1][j].distance != 0) {
                // down
                ObjList_append(temp_list, &obj_map[i + 1][j]);
            }
            if (j - 1 > 0 && obj_map[i][j - 1].distance != 0) {
                //left
                ObjList_append(temp_list, &obj_map[i][j - 1]);
            }
            if (j + 1 < WEEK3_MIGONG_MIGONG_SIZE && obj_map[i][j + 1].distance != 0) {
                //right
                ObjList_append(temp_list, &obj_map[i][j + 1]);
            }
        }
    }
}


void DijkstraInMap(DijkstraTable *table, int vertex_number, int(*smallest)(DijkstraTable *, int)){
    int i, si;
    MapVertex * temp_vertex, *vertex;
    for(;;){
        si = smallest(table, vertex_number);
        if (si == -1) break;
        vertex = ObjList_get(table[si].header, 0);
        if(vertex == NULL) break;
        table[vertex->index_in_table].known = 1;
        i = 1;
        temp_vertex = ObjList_get(table[vertex->index_in_table].header, i++);
        while(temp_vertex!=NULL) {
            if(!table[temp_vertex->index_in_table].known)
                if(table[vertex->index_in_table].dist + vertex->distance < table[temp_vertex->index_in_table].dist){
                    table[temp_vertex->index_in_table].dist = table[vertex->index_in_table].dist + vertex->distance;
                    table[temp_vertex->index_in_table].path = vertex->index_in_table;
                }
            temp_vertex = ObjList_get(table[vertex->index_in_table].header, i++);
        }
    }
}


int findSmallestUnknownDistanceVertexInTable(DijkstraTable * table, int vertex_num){
    int smallest = -1;
    int mmax = WEEK3_MIGONG_MIGONG_SIZE * WEEK3_MIGONG_MIGONG_SIZE;
    int i;
    for(i=0; i < vertex_num; ++i){
        if(table[i].known==0) smallest = i;
    }
    for(;i<vertex_num;++i){
        if (table[i].known == 0 && table[i].dist < table[smallest].dist) {
            smallest = i;
        }
    }
    return smallest;
}


int migong_main() {
    int migong_map[WEEK3_MIGONG_MIGONG_SIZE][WEEK3_MIGONG_MIGONG_SIZE];
    int i, j, temp1, start;
    int vertex_num = 0;
    DijkstraTable *table;
    MapVertex (*obj_map)[WEEK3_MIGONG_MIGONG_SIZE];
    random_init();
    for (i = 0; i < WEEK3_MIGONG_MIGONG_SIZE; ++i)
        for (j = 0; j < WEEK3_MIGONG_MIGONG_SIZE; ++j) {
            temp1 = random_int_range(0, 2);
            switch (temp1) {
                case 0:
                    migong_map[i][j] = 0;
                    break;
                case 1:
                    migong_map[i][j] = 1;
                    ++vertex_num;
                    break;
                case 2:
                    migong_map[i][j] = 10;
                    ++vertex_num;
                    break;
                default:
                    /*error*/
                    migong_map[i][j] = 0;
                    break;
            }

        }
    table = malloc(sizeof(DijkstraTable) * vertex_num);
    obj_map = (void *)transportIntegerMap2ObjMap(migong_map);
    //read
    start = 0;
    initTable(table, obj_map, vertex_num, start, readGraphFromIntegerMap);
    DijkstraInMap(table,vertex_num, findSmallestUnknownDistanceVertexInTable);

}
