#include <haar_transformation.h>

#include <stdio.h>

#define COORD(i, j, source, img) source.img[(i) * source.width + (j)]
#define COORD_S(i, j, source, img) source.img[(i) * (source.width / 2) + (j)]
#define P1(i, j, source) COORD(2 * (i), 2 * (j), source, original_image)
#define P2(i, j, source) COORD(2 * (i), 2 * (j) + 1, source, original_image)
#define P3(i, j, source) COORD(2 * (i) + 1, 2 * (j), source, original_image)
#define P4(i, j, source) COORD(2 * (i) + 1, 2 * (j) + 1, source, original_image)
void
haar_transformation_transform
(
  haar_transformation_DATA_SOURCE data_source
)
{
  unsigned i = 0, j = 0;
  for (i = 0; i < (data_source.height - 1) / 2; ++i)
  {
    for (j = 0; j < (data_source.width - 1) / 2; ++j)
    {
      COORD_S(i, j, data_source, avg_image) = 0.25 * (P1(i, j, data_source)
                                                      + P2(i, j, data_source)
                                                      + P3(i, j, data_source)
                                                      + P4(i, j, data_source));
                                           
      COORD_S(i, j, data_source, vertical_edges) = 0.25 * (P1(i, j, data_source)
                                                           + P3(i, j, data_source)
                                                           - P2(i, j, data_source)
                                                           - P4(i, j, data_source));

      COORD_S(i, j, data_source, horizontal_edges) = 0.25 * (P1(i, j, data_source)
                                                             + P2(i, j, data_source)
                                                             - P3(i, j, data_source)
                                                             - P4(i, j, data_source));

      COORD_S(i, j, data_source, diagonal_edges) = 0.25 * (P1(i, j, data_source)
                                                           + P4(i, j, data_source)
                                                           - P2(i, j, data_source)
                                                           - P3(i, j, data_source));
    }
  }
  /*printf("Transofrm\n");
  for (i = 0; i < data_source.height; ++i)
    for (j = 0; j < data_source.width; ++j)
      printf("%d, %d: %d\n", (int)i, (int)j, (int) COORD(i, j, data_source, original_image));*/
}

void 
haar_transformation_inverse_transformation
(
  haar_transformation_DATA_SOURCE data_source
)
{
  unsigned i = 0, j = 0;
  for (i = 0; i < (data_source.height - 1) / 2; ++i)
  {
    for (j = 0; j < (data_source.width - 1) / 2; ++j)
    {
      P1(i, j, data_source) = COORD_S(i, j, data_source, avg_image)
                              + COORD_S(i, j, data_source, vertical_edges)
                              + COORD_S(i, j, data_source, horizontal_edges)
                              + COORD_S(i, j, data_source, diagonal_edges);
      P2(i, j, data_source) = COORD_S(i, j, data_source, avg_image)
                              + COORD_S(i, j, data_source, horizontal_edges)
                              - COORD_S(i, j, data_source, vertical_edges)
                              - COORD_S(i, j, data_source, diagonal_edges);
      P3(i, j, data_source) = COORD_S(i, j, data_source, avg_image)
                              + COORD_S(i, j, data_source, vertical_edges)
                              - COORD_S(i, j, data_source, horizontal_edges)
                              - COORD_S(i, j, data_source, diagonal_edges);
      P4(i, j, data_source) = COORD_S(i, j, data_source, avg_image)
                              + COORD_S(i, j, data_source, diagonal_edges)
                              - COORD_S(i, j, data_source, vertical_edges)
                              - COORD_S(i, j, data_source, horizontal_edges);
    }
  }
 /* for (i = 0; i < data_source.height; ++i)
    for (j = 0; j < data_source.width; ++j)
      printf("%d, %d: %d\n", (int) i,(int) j,(int) COORD(i, j, data_source, original_image));*/
}
#undef COORD
#undef P1
#undef P2
#undef P3
#undef P4

