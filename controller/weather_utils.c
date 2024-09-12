#include <stdio.h>
#include <stdbool.h> 
#include <curl/curl.h> 
#include <json-c/json.h>
#include <time.h>
#include "weather_utils.h"
#include "utils.h"

int getCurrentWeather(struct json_object *weather_data, req_params_t *params){
    return true;
}

int getWeatherForecast(struct json_object *weather_data, uint8_t days, req_params_t *params){
    return true;

}

int evaluateWeatherData(struct json_object *weather_data, req_params_t *params){
    return true;
}

int getRequestData(req_params_t *req_params){
    int api_file = readDataFromFile(API_KEY_FILENAME, &req_params->api_key);
    int coords_file = readDataFromFile(LOCATION_FILENAME, &req_params->coords);
    
    if(api_file == ALLOCATION_ERR || coords_file == ALLOCATION_ERR) return ALLOCATION_ERR;
    if(api_file == FILE_NOT_FOUND_ERR || coords_file == FILE_NOT_FOUND_ERR) return FILE_NOT_FOUND_ERR;

    req_params->days = 0;
    return EXIT_SUCCESS;
}


int readDataFromFile(char *filename, char **buffer){
    FILE *data_file = fopen(filename, "r");
    if(data_file == NULL){
        fprintf(stderr, FILE_NOT_FOUND_ERR_MSG ,filename);
        return FILE_NOT_FOUND_ERR;
    }
    int buf_capacity = API_KEY_LENGHT + 1;
    *buffer = (char*)malloc(buf_capacity * sizeof(char));
    if(buffer == NULL){
        fprintf(stderr, ALLOC_ERR_MSG);
        return ALLOCATION_ERR;
    }
    char c;
    int i = 0;
    while ((c = fgetc(data_file)) != '\n' && c != EOF)
    {
        if(i >= buf_capacity){
            buf_capacity = buf_capacity*2;
            char *tmp = (char*)realloc(*buffer, buf_capacity+1);
            if(tmp == NULL){
                fprintf(stderr, ALLOC_ERR_MSG);
                fclose(data_file);
                return ALLOCATION_ERR;
            }
            *buffer = tmp;
        }
        (*buffer)[i] = c;
        i++;
    }
    (*buffer)[i] = '\0';
    fclose(data_file);
    return EXIT_SUCCESS;
}


