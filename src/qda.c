// qda.c - a quantitative data analyzer

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int compare(const void *p1, const void *p2) {
  double d1 = *(const double *) p1;
  double d2 = *(const double *) p2;

  return d1 < d2 ? -1 : d1 > d2 ? 1 : 0;
}

static double median(const double ds[], int count) {
  int mid = count / 2;

  return count % 2 ? ds[mid] : (ds[mid] + ds[mid - 1]) / 2;
}

int main(int argc, char *argv[]) {
  int count = argc - 1;

  double ds[count];
  double total = 0;
  double sum_of_squares = 0;
  double sum_of_reciprocals = 0;
  double product = 1;

  ++argv;

  for (int i = 0; i < count; ++i) {
    ds[i] = atof(argv[i]);
    total += ds[i];
    sum_of_squares += ds[i] * ds[i];
    sum_of_reciprocals += 1 / ds[i];
    product *= ds[i];
  }

  qsort(ds, count, sizeof ds[0], compare);

  double min = ds[0];
  double max = ds[count - 1];

  double range     =  max - min;
  double mid_range = (max + min) / 2;

  int half = count / 2;

  double q2 = median(ds, count);

  _Bool single_element = count == 1;

  double q1 = single_element ? q2 : median(ds, half);
  double q3 = single_element ? q2 : median(ds + count - half, half);

  double iqr       =  q3 - q1;
  double mid_hinge = (q3 + q1) / 2;

  double am = total / count;
  double gm = pow(product, 1.0 / count);
  double qm = sqrt(sum_of_squares / count);
  double hm = 1 / (sum_of_reciprocals / count);

  double sum_of_deviation_to_2 = 0;
  double sum_of_deviation_to_3 = 0;
  double sum_of_deviation_to_4 = 0;

  for (int i = 0; i < count; ++i) {
    double deviation = ds[i] - am;
    double deviation_to_2 = deviation * deviation;

    sum_of_deviation_to_2 += deviation_to_2;
    sum_of_deviation_to_3 += deviation_to_2 * deviation;
    sum_of_deviation_to_4 += deviation_to_2 * deviation_to_2;
  }

  double var = sum_of_deviation_to_2 / count;
  double sd  = sqrt(var);
  double rsd = sd / fabs(am);

  double sd_to_3 = sd * sd * sd;
  double sd_to_4 = sd_to_3 * sd;

  double skewness = sum_of_deviation_to_3 / count / sd_to_3;
  double kurtosis = sum_of_deviation_to_4 / count / sd_to_4;

  printf("                      Count = %d\n",    count);
  printf("                      Total = %.10g\n", total);
  printf("                    Minimum = %.10g\n", min);
  printf("                    Maximum = %.10g\n", max);
  printf("                      Range = %.10g\n", range);
  printf("                  Mid-Range = %.10g\n", mid_range);
  printf("             First Quartile = %.10g\n", q1);
  printf("            Second Quartile = %.10g\n", q2);
  printf("             Third Quartile = %.10g\n", q3);
  printf("        Interquartile Range = %.10g\n", iqr);
  printf("                  Mid-Hinge = %.10g\n", mid_hinge);
  printf("            Arithmetic Mean = %.10g\n", am);
  printf("             Quadratic Mean = %.10g\n", qm);
  printf("             Geometric Mean = %.10g\n", gm);
  printf("              Harmonic Mean = %.10g\n", hm);
  printf("                   Variance = %.10g\n", var);
  printf("         Standard Deviation = %.10g\n", sd);
  printf("Relative Standard Deviation = %.10g\n", rsd);
  printf("                   Skewness = %.10g\n", skewness);
  printf("                   Kurtosis = %.10g\n", kurtosis);
}