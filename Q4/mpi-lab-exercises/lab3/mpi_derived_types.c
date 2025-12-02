/*
  STL file format 

  UINT8[80] – Header
  UINT32 – Number of triangles

  foreach triangle
  REAL32[3] – Normal vector
  REAL32[3] – Vertex 1
  REAL32[3] – Vertex 2
  REAL32[3] – Vertex 3
  UINT16 – Attribute byte count
  end

  (see https://en.wikipedia.org/wiki/STL_(file_format)
  
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <mpi.h>

#define STL_HDR_SIZE 80

typedef struct {
  float n[3];			/* Normal vector */
  float v1[3];			/* Vertex 1 */
  float v2[3];			/* Vertex 2 */
  float v3[3];			/* Vertex 3 */
  uint16_t attrib;		/* Attribute byte count */
} __attribute__((packed)) stl_triangle_t;

typedef struct {
  char hdr[STL_HDR_SIZE];	/* Header */
  uint32_t n_tri;		/* Number of triangles */
  stl_triangle_t *tri;		/* Triangles */
} stl_model_t;


void stl_read(const char *fname, stl_model_t *model) {
    MPI_File fh;
    MPI_Datatype MPI_STL_TRI;
    MPI_Comm comm = MPI_COMM_WORLD;

    int rank;
    MPI_Comm_rank(comm, &rank);

    /* Derived type for one triangle */
    MPI_Type_contiguous(sizeof(stl_triangle_t), MPI_BYTE, &MPI_STL_TRI);
    MPI_Type_commit(&MPI_STL_TRI);

    /* Open collectively */
    MPI_File_open(comm, fname, MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);

    /* 1. Read header */
    MPI_File_read_at_all(fh, 0,
                         model->hdr, STL_HDR_SIZE,
                         MPI_BYTE, MPI_STATUS_IGNORE);

    if (strncmp(model->hdr, "solid", 5) == 0) {
        if (rank == 0) fprintf(stderr, "ASCII STL not supported\n");
        MPI_Abort(comm, 1);
    }

    /* 2. Read triangle count */
    MPI_File_read_at_all(fh, STL_HDR_SIZE,
                         &model->n_tri, 1,
                         MPI_UNSIGNED, MPI_STATUS_IGNORE);

    if (rank == 0)
        printf("Found: %u triangles\n", model->n_tri);

    /* Allocate full triangle array on each rank */
    model->tri = malloc(model->n_tri * sizeof(stl_triangle_t));

    /* 3. Read all triangles collectively */
    MPI_Offset tri_offset = STL_HDR_SIZE + sizeof(uint32_t);

    MPI_File_read_at_all(fh, tri_offset,
                         model->tri,
                         model->n_tri,
                         MPI_STL_TRI,
                         MPI_STATUS_IGNORE);

    MPI_File_close(&fh);
    MPI_Type_free(&MPI_STL_TRI);

    if (rank == 0) printf("Done\n");
}

void stl_write(const char *fname, stl_model_t *model) {
    MPI_File fh;
    MPI_Datatype MPI_STL_TRI;
    MPI_Comm comm = MPI_COMM_WORLD;

    int rank;
    MPI_Comm_rank(comm, &rank);

    /* Derived type for triangles */
    MPI_Type_contiguous(sizeof(stl_triangle_t), MPI_BYTE, &MPI_STL_TRI);
    MPI_Type_commit(&MPI_STL_TRI);

    /* Open collectively */
    MPI_File_open(comm, fname,
                  MPI_MODE_CREATE | MPI_MODE_WRONLY,
                  MPI_INFO_NULL, &fh);

    /* 1. Write header */
    MPI_File_write_at_all(fh, 0,
                          model->hdr, STL_HDR_SIZE,
                          MPI_BYTE, MPI_STATUS_IGNORE);

    /* 2. Write triangle count */
    MPI_File_write_at_all(fh, STL_HDR_SIZE,
                          &model->n_tri, 1,
                          MPI_UNSIGNED, MPI_STATUS_IGNORE);

    /* 3. Write all triangles */
    MPI_Offset tri_offset = STL_HDR_SIZE + sizeof(uint32_t);

    MPI_File_write_at_all(fh, tri_offset,
                          model->tri,
                          model->n_tri,
                          MPI_STL_TRI,
                          MPI_STATUS_IGNORE);

    MPI_File_close(&fh);
    MPI_Type_free(&MPI_STL_TRI);

    if (rank == 0) printf("Done\n");
}

int main(int argc, char **argv) {
  stl_model_t model;
  
  MPI_Init(&argc, &argv);
  
  stl_read("./data/sphere.stl", &model);
  stl_write("out.stl", &model);
  free(model.tri);

  MPI_Finalize();
  
  return 0;
}


