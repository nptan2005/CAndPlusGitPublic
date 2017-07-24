/* Tinh da thuc bac N */
#define MAX 100

float tinhdathuc(float heso[], float x, int n)
{
  float tong = 0.0;
  int i;

  for (i=0; i<n; i++)
  {
    tong = (tong + heso[i]) * x;
  }
  tong += heso[n];
  return tong;
}

void main()
{
  float heso[MAX], x;
  int n, i;

  printf("\nCho biet so bac : ");
  scanf("%d", &n);
  printf("\nNhap vao cac he so :");
  for (i=0; i<=n; i++)
    scanf("%f", &heso[i]);
  printf("\nNhap vao gia tri X : ");
  scanf("%f", &x);
  printf("\nKet qua tinh = %f", tinhdathuc(heso, x, n));
  getch();
}