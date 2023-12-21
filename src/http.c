#include "http.h"

map_t *parse_http_req(char *req)
{
    int len = strlen(req);
    req = string_removechar('\r', req, len);
    list_t *lines = split('\n', req, strlen(req));
    list_popback(lines);
    list_popback(lines);

    list_t *vl = lines;

    list_t *vc = split(' ', vl->value, strlen(vl->value));

    if (list_len(vc) != 3)
    {
        fprintf(stderr, "Invalid request\n");
        return NULL;
    }

    map_t *map = map_create();

    map_add(
        map,
        "method",
        list_get(vc, 0));

    map_add(
        map,
        "url",
        list_get(vc, 1));

    map_add(
        map,
        "Http-Version",
        list_get(vc, 2));

    vl = vl->next;

    list_destroy(vc);

    while (vl != NULL)
    {
        vc = split_lim(':', vl->value, strlen(vl->value), 2);
        if (list_len(vc) != 2)
        {
            list_destroy(vc);
            vl = vl->next;
            continue;
        }

        char *ss = trim(list_get(vc, 1));
        char *sk = trim(list_get(vc, 0));

        char *sslow = string_to_lower(ss);
        char *sklow = string_to_lower(sk);

        if(!strcmp(sklow,"sec-websocket-key")){
            map_add(map, sklow, ss);
        }else{
            map_add(map, sklow, sslow);
        }

        free(sslow);
        free(sklow);
        free(ss);
        free(sk);

        list_destroy(vc);
        vl = vl->next;
    }

    free(req);
    return map;
}
