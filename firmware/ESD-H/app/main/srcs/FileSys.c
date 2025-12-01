#include "FileSys.h"

esp_vfs_spiffs_conf_t conf;

void fs_init( void){
    ESP_LOGI(TAG_FS, "initialization in progress");

     
      conf.base_path = "/spiffs"; // here "/" is root and "/spiffs" is our spiffs partition
      conf.partition_label = NULL; // start from partition label
      conf.max_files = 5; //this tells how many files spiffs can open
      conf.format_if_mount_failed = true; //intimidation of mount status
    esp_vfs_spiffs_register(&conf);
}

void fs_deinit( void ){
    esp_vfs_spiffs_unregister(conf.partition_label);
}

void file_test( void ){
    ESP_LOGI(TAG_FS, "Opening file");
    FILE *f;
    f = fopen("/spiffs/test.txt","w");
    fprintf(f,"Hello Medium People Do you like my Blogs?");
    fclose(f);
    ESP_LOGI(TAG_FS,"File written");

    f= fopen("/spiffs/test.txt", "r");
    char line[64];
    fgets(line, sizeof(line), f);//reads line from stream
    fclose(f);
    ESP_LOGI(TAG_FS, "Read from file: '%s'", line);
}