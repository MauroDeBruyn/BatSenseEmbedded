#include "FileSYS.h"

static const char *TAG_FS = "spiffs";
esp_vfs_spiffs_conf_t conf;

void fs_init( void){
    ESP_LOGI(TAG_FS, "initialization in progress");

    esp_err_t ret;
     
      conf.base_path = "/spiffs"; // here "/" is root and "/spiffs" is our spiffs partition
      conf.partition_label = NULL; // start from partition label
      conf.max_files = 5; //this tells how many files spiffs can open
      conf.format_if_mount_failed = false; //intimidation of mount status
    ret = esp_vfs_spiffs_register(&conf);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG_FS, "SPIFFS mount failed: %s", esp_err_to_name(ret));
        return;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(NULL, &total, &used);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG_FS, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
    } else {
        ESP_LOGI(TAG_FS, "Partition size: total: %d, used: %d", total, used);
    }
}

void ls_spiffs(const char *path)
{
    DIR *dir = opendir(path);
    if (!dir) {
        ESP_LOGE("LS", "opendir failed for %s", path);
        return;
    }

    struct dirent *ent;
    while ((ent = readdir(dir)) != NULL) {
        char fullpath[256];
        struct stat st;

        int len = snprintf(fullpath, sizeof(fullpath),
                           "%s/%s", path, ent->d_name);

        if (len < 0 || len >= sizeof(fullpath)) {
            ESP_LOGE("LS", "Path too long: %s/%s", path, ent->d_name);
            continue;
        }

        if (stat(fullpath, &st) == 0) {
            ESP_LOGI("LS", "%s  %ld bytes",
                     ent->d_name,
                     st.st_size);
        } else {
            ESP_LOGI("LS", "%s", ent->d_name);
        }
    }

    closedir(dir);
}

void fs_deinit( void ){
    esp_vfs_spiffs_unregister(conf.partition_label);
}

void file_test(void)
{
    FILE *f = fopen("/spiffs/index.html", "r");
    if (!f) {
        ESP_LOGE("SPIFFS", "Failed to open file");
        return;
    }

    char buf[1024];
    size_t len = fread(buf, 1, sizeof(buf) - 1, f);
    buf[len] = 0;

    ESP_LOGI("SPIFFS", "CONTENT:\n%s", buf);

    fclose(f);
}