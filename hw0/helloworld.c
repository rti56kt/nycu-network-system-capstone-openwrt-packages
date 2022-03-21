#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *if_name;
  char *if_mac_addr;
  char *if_status;
} if_info;

typedef struct {
  if_info wan;
  if_info wifi24;
  if_info wifi5;
} ifs_checker;

char *getOperState(char *ifname) {
  char *filename = (char *)malloc(
      (strlen("/sys/class/net//operstate") + strlen(ifname)) * sizeof(char) +
      1);
  char *line = NULL;
  size_t line_size = 0;
  ssize_t read_len = 0;
  FILE *fp = NULL;

  sprintf(filename, "/sys/class/net/%s/operstate", ifname);

  fp = fopen(filename, "r");
  if (fp == NULL) {
    return NULL;
  } else {
    read_len = getline(&line, &line_size, fp);
    fclose(fp);

    if (line[read_len - 1] == '\n') {
      line[read_len - 1] = '\0';
      read_len--;
    }

    return line;
  }
}

char *getMacAddr(char *ifname) {
  char *filename = (char *)malloc(
      (strlen("/sys/class/net//address") + strlen(ifname)) * sizeof(char) + 1);
  char *line = NULL;
  size_t line_size = 0;
  ssize_t read_len = 0;
  FILE *fp = NULL;

  sprintf(filename, "/sys/class/net/%s/address", ifname);

  fp = fopen(filename, "r");
  if (fp == NULL) {
    return NULL;
  } else {
    read_len = getline(&line, &line_size, fp);
    fclose(fp);

    if (line[read_len - 1] == '\n') {
      line[read_len - 1] = '\0';
      read_len--;
    }

    return line;
  }
}

int main() {
  char wan_ifname[] = "eth0";
  char wifi24_ifname[] = "wlan0";
  char wifi5_ifname[] = "wlan1";
  ifs_checker ifs;

  ifs.wan.if_name = wan_ifname;
  ifs.wan.if_mac_addr = getMacAddr(wan_ifname);
  ifs.wan.if_status = getOperState(wan_ifname);
  printf("%s\n", ifs.wan.if_mac_addr == NULL ? "NULL" : ifs.wan.if_mac_addr);

  ifs.wifi24.if_name = wifi24_ifname;
  ifs.wifi24.if_mac_addr = getMacAddr(wifi24_ifname);
  ifs.wifi24.if_status = getOperState(wifi24_ifname);
  printf("%s\n",
         ifs.wifi24.if_mac_addr == NULL ? "NULL" : ifs.wifi24.if_mac_addr);

  ifs.wifi5.if_name = wifi5_ifname;
  ifs.wifi5.if_mac_addr = getMacAddr(wifi5_ifname);
  ifs.wifi5.if_status = getOperState(wifi5_ifname);
  printf("%s\n",
         ifs.wifi5.if_mac_addr == NULL ? "NULL" : ifs.wifi5.if_mac_addr);

  return 0;
}