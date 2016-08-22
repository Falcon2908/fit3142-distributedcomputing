int get_kth_bit(int num, int k){
  int mask =  1 << k;
  int masked_n = num & mask;
  int thebit = masked_n >> k;
  return thebit;
}

int toggle_bit(int num, int k){
  num ^= 1 << k;
  return num;
}
