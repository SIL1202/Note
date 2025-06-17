#include <stdio.h>
#include <stdlib.h>

void merge(int *, int *, int, int);
void mergeSort(int *, int);

int main() {
  int nums[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  int n = 10;
  mergeSort(nums, n);
  for (int i = 0; i < n; i++)
    printf("%d ", nums[i]);
  return 0;
}

void merge(int *nums, int *tmp, int l, int r) {
  if (l >= r)
    return;
  int mid = l + (r - l) / 2;
  merge(nums, tmp, l, mid);
  merge(nums, tmp, mid + 1, r);

  int i = l, j = mid + 1, k = l;
  while (i <= mid && j <= r)
    tmp[k++] = nums[i] <= nums[j] ? nums[i++] : nums[j++];

  while (i <= mid)
    tmp[k++] = nums[i++];
  while (j <= r)
    tmp[k++] = nums[j++];

  for (int i = l; i <= r; i++)
    nums[i] = tmp[i];
}

void mergeSort(int *nums, int n) {
  int *tmp = malloc(sizeof(int) * n);
  merge(nums, tmp, 0, n - 1);
  free(tmp);
}
