//
// Created by Calun on 2021/1/16.
//

#include "migong.h"
#include "../calunvier/tools.h"
#include "../objects/list.h"
#include <stdlib.h>
#include <stdio.h>

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

int new_point_to_index(int x, int y)
{
    return y * WEEK3_MIGONG_MIGONG_SIZE + x;
}

void initTable(DijkstraTable *table, void *graph, int vertex_number, void (*readGraph)(void *, DijkstraTable *)) {
    int i;
    readGraph(graph, table);
    for (i = 0; i < vertex_number; i++) {
        table[i].dist = MAX_INT;
        table[i].known = 0;
        table[i].path = -1;
    }
}

MapVertex *transportIntegerMap2ObjMap(int (*_int_map)[]) {
    int y, x, (*int_map)[WEEK3_MIGONG_MIGONG_SIZE] = _int_map;
    MapVertex (*objMap)[WEEK3_MIGONG_MIGONG_SIZE] = malloc(
            sizeof(MapVertex) * WEEK3_MIGONG_MIGONG_SIZE * WEEK3_MIGONG_MIGONG_SIZE);
    for (y = 0; y < WEEK3_MIGONG_MIGONG_SIZE; ++y) {
        for (x = 0; x < WEEK3_MIGONG_MIGONG_SIZE; ++x) {
            objMap[y][x].y = y;
            objMap[y][x].x = x;
            objMap[y][x].distance = int_map[y][x];
            objMap[y][x].index_in_table = -1;
        }
    }
    return (MapVertex *) objMap;
}


void readGraphFromIntegerMap(void * _int_map, DijkstraTable *table) {
    int y, x, v = 0;
    MapVertex (*obj_map)[WEEK3_MIGONG_MIGONG_SIZE] = _int_map;
    ObjList temp_list;
    for (y = 0; y < WEEK3_MIGONG_MIGONG_SIZE; ++y) {
        for (x = 0; x < WEEK3_MIGONG_MIGONG_SIZE; ++x) {
            //Check if is 0
            if (obj_map[y][x].distance == 0) continue;
            else {
                table[v++].header = (temp_list = newObjList(sizeof(MapVertex)));
                ObjList_append(temp_list, &obj_map[y][x]);
                obj_map[y][x].index_in_table = v - 1;
            }

            if (y - 1 >= 0 && obj_map[y - 1][x].distance != 0) {
                // up
                ObjList_append(temp_list, &obj_map[y - 1][x]);
            }
            if (y + 1 < WEEK3_MIGONG_MIGONG_SIZE && obj_map[y + 1][x].distance != 0) {
                // down
                ObjList_append(temp_list, &obj_map[y + 1][x]);
            }
            if (x - 1 >= 0 && obj_map[y][x - 1].distance != 0) {
                //left
                ObjList_append(temp_list, &obj_map[y][x - 1]);
            }
            if (x + 1 < WEEK3_MIGONG_MIGONG_SIZE && obj_map[y][x + 1].distance != 0) {
                //right
                ObjList_append(temp_list, &obj_map[y][x + 1]);
            }
        }
    }
}


void DijkstraInMap(DijkstraTable *table, int vertex_number, int start, int(*smallest)(DijkstraTable *, int)){
    int i, si;
    MapVertex * temp_vertex, *vertex;
    table[start].dist = 0;
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
        if (table[i].known == 0)
        {
            smallest = i;
            break;
        }
    }
    for(++i;i<vertex_num;++i){
        if (table[i].known == 0 && table[i].dist < table[smallest].dist) {
            smallest = i;
        }
    }
    return smallest;
}


void print_migong(MapVertex *_obj_map){
    MapVertex (*obj_map)[WEEK3_MIGONG_MIGONG_SIZE] = (void *)_obj_map;
    int y, x;
    for (y = 0; y < WEEK3_MIGONG_MIGONG_SIZE; ++y){
        for (x = 0; x < WEEK3_MIGONG_MIGONG_SIZE; ++x) {
            switch (obj_map[y][x].distance) {
                case 0:
                    printf("©–");
                    break;
                case 1:
                    printf("Ò¼");
                    break;
                case 10:
                    printf("Ê°");
                    break;
                default:
                    printf("V");
                    break;
            }
        }
        printf("\n");
    }
}


void findPath(DijkstraTable *table,MapVertex *obj_map, int end, ObjList path_list){
    DijkstraTable t;
    MapVertex * vertex;
    t = table[obj_map[end].index_in_table];
    if (t.dist == MAX_INT) return;
    while (t.dist) {
        vertex = ((MapVertex *)ObjList_get(t.header, 0));
        vertex->distance = 3;
        ObjList_insert(path_list, vertex, 0);
        t = table[t.path];
    }
    vertex = ((MapVertex *)ObjList_get(t.header, 0));
    vertex->distance = 3;
    ObjList_insert(path_list, vertex, 0);
}


int migong_main() {
    int migong_map[WEEK3_MIGONG_MIGONG_SIZE][WEEK3_MIGONG_MIGONG_SIZE];
    int y, x, temp1, start, end;
    int vertex_num = 0;
    ObjList path_list;
    ObjListIterator map_iterator;
    DijkstraTable *table;
    MapVertex (*obj_map)[WEEK3_MIGONG_MIGONG_SIZE], *vertex;
    random_init();
    for (y = 0; y < WEEK3_MIGONG_MIGONG_SIZE; ++y)
        for (x = 0; x < WEEK3_MIGONG_MIGONG_SIZE; ++x) {
            temp1 = random_int_range(0, 2);
            switch (temp1) {
                case 0:
                    migong_map[y][x] = 0;
                    break;
                case 1:
                    migong_map[y][x] = 1;
                    ++vertex_num;
                    break;
                case 2:
                    migong_map[y][x] = 10;
                    ++vertex_num;
                    break;
                default:
                    /*error*/
                    migong_map[y][x] = 0;
                    break;
            }

        }
    table = malloc(sizeof(DijkstraTable) * vertex_num);
    obj_map = (void *)transportIntegerMap2ObjMap(migong_map);
    print_migong((MapVertex *)obj_map);
    //read
    printf("Please input the start point(x y):");
    scanf("%d %d", &x, &y);
    start = new_point_to_index(x, y);
    printf("Please input the end point(x y):");
    scanf("%d %d", &x, &y);
    end = new_point_to_index(x, y);
    initTable(table, obj_map, vertex_num, readGraphFromIntegerMap);
    DijkstraInMap(table,vertex_num, ((MapVertex *)obj_map)[start].index_in_table, findSmallestUnknownDistanceVertexInTable);
    path_list = newObjList(sizeof(MapVertex));
    findPath(table, (MapVertex *)obj_map, end, path_list);
    print_migong((MapVertex*)obj_map);

    map_iterator = ObjList_getIterator(path_list);
    vertex = ObjListIterator_next(map_iterator);
    printf("(%d, %d, %d)", vertex->x, vertex->y, vertex->distance);
    while (vertex = ObjListIterator_next(map_iterator)) {
        printf("->(%d, %d, %d)", vertex->x, vertex->y, vertex->distance);
    }
    return 0;
}
