// sumber.c - print a statistical summary of input numbers

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int compare(const void *p1, const void *p2) {
  double d1 = *(const double *) p1;
  double d2 = *(const double *) p2;

  return d1 < d2 ? -1 : d1 > d2 ? 1 : 0;
}

static double median(const double ds[], size_t count) {
  size_t mid = count / 2;

  return count % 2 ? ds[mid] : (ds[mid] + ds[mid - 1]) / 2;
}

int main(void) {
  size_t max_capacity = SIZE_MAX / sizeof (double);
  size_t capacity = 256;
  size_t count = 0;

  double sum = 0;
  double product = 1;

  double *ds = malloc(capacity * sizeof *ds);

  if (!ds)
    return 1;

  while (scanf("%lg", &ds[count]) == 1) {
    sum += ds[count];
    product *= ds[count];

    if (++count == capacity)
      if ((capacity *= 2) > max_capacity ||
          !(ds = realloc(ds, capacity * sizeof *ds)))
        return 2;
  }

  if (count < 2)
    return 3;

  qsort(ds, count, sizeof ds[0], compare);

  double min = ds[0];
  double max = ds[count - 1];

  double range     =  max - min;
  double mid_range = (max + min) / 2;

  size_t half = count / 2;

  double q1 = median(ds, half);
  double q2 = median(ds, count);
  double q3 = median(ds + count - half, half);

  double iqr       =  q3 - q1;
  double mid_hinge = (q3 + q1) / 2;

  double am = sum / count;
  double gm = pow(product, 1.0 / count);

  double sum_of_deviation_to_2 = 0;
  double sum_of_deviation_to_3 = 0;
  double sum_of_deviation_to_4 = 0;

  for (size_t i = 0; i < count; ++i) {
    double deviation      = ds[i] - am;
    double deviation_to_2 = deviation * deviation;

    sum_of_deviation_to_2 += deviation_to_2;
    sum_of_deviation_to_3 += deviation_to_2 * deviation;
    sum_of_deviation_to_4 += deviation_to_2 * deviation_to_2;
  }

  free(ds);

  double sd      = sqrt(sum_of_deviation_to_2 / count);
  double sd_to_3 = sd * sd * sd;
  double sd_to_4 = sd_to_3 * sd;

  double skewness = sum_of_deviation_to_3 / count / sd_to_3;
  double kurtosis = sum_of_deviation_to_4 / count / sd_to_4;

  // 10 is the precision of my CASIO fx-991ES PLUS calculator
  printf("              Count = %zu\n",   count);
  printf("                Sum = %.10g\n", sum);
  printf("            Minimum = %.10g\n", min);
  printf("            Maximum = %.10g\n", max);
  printf("              Range = %.10g\n", range);
  printf("          Mid-Range = %.10g\n", mid_range);
  printf("     First Quartile = %.10g\n", q1);
  printf("    Second Quartile = %.10g\n", q2);
  printf("     Third Quartile = %.10g\n", q3);
  printf("Interquartile Range = %.10g\n", iqr);
  printf("          Mid-Hinge = %.10g\n", mid_hinge);
  printf("    Arithmetic Mean = %.10g\n", am);
  printf("     Geometric Mean = %.10g\n", gm);
  printf(" Standard Deviation = %.10g\n", sd);
  printf("           Skewness = %.10g\n", skewness);
  printf("           Kurtosis = %.10g\n", kurtosis);
}
