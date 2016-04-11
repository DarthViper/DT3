//==============================================================================
///
///    File: TWMWriter.cpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/Media/TWMWriter.hpp"
#include "DT3Core/Types/FileBuffer/BinaryFileStream.hpp"
#include "DT3Core/Types/Graphics/Mesh.hpp"
#include "DT3Core/System/FileManager.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
//==============================================================================

DTsize TWMWriter::begin_export_section (BinaryFileStream &file, int32_t section)
{
    file << section;
    DTsize size_location = file.p();
    file << (int32_t) 0;

    return size_location;
}

void TWMWriter::end_export_section (BinaryFileStream &file, DTsize size_location)
{
    DTsize save_location = file.p();
    file.seek_p(size_location, Stream::FROM_BEGINNING);
    file << (int32_t) (save_location-size_location-sizeof(int32_t));
    file.seek_p(save_location, Stream::FROM_BEGINNING);
}

void TWMWriter::write (const FilePath &pathname, const std::list<std::shared_ptr<Mesh>> &meshes)
{
    // Open the file
    BinaryFileStream    file;
    FileManager::open(file, pathname, false);

    //
    // Write header
    //

    uint32_t magic = MAGIC;
    file << magic;

    uint32_t version = (1 << 24) | (0 << 16) | (0 << 8) | (0 << 0);       // 1.0.0.0
    file << version;

    //
    // Write data
    //

    // FILE
    DTsize file_location = begin_export_section(file, FILE);

    // MESHES
    DTsize meshes_location = begin_export_section(file, MESHES);

    file << (int32_t) meshes.size();

    for (auto mesh : meshes) {
        // MESHES
        DTsize mesh_location = begin_export_section(file, MESHES_MESH);


        // MESH_NAME
        DTsize mesh_name = begin_export_section(file, MESHES_MESH_NAME);
        file << mesh->name();
        end_export_section(file, mesh_name); // MESH_NAME


        // MESHES_MESH_POSITIONS
        DTsize mesh_position = begin_export_section(file, MESHES_MESH_POSITIONS);

        std::vector<Vector3> vertex_stream = mesh->vertex_stream();
        file << (int32_t) vertex_stream.size();
        for (size_t i = 0; i < vertex_stream.size(); ++i) {
            file << (DTfloat) vertex_stream[i].x;
            file << (DTfloat) vertex_stream[i].y;
            file << (DTfloat) vertex_stream[i].z;
        }

        end_export_section(file, mesh_position); // MESHES_MESH_POSITIONS


        // MESHES_MESH_NORMALS
        DTsize mesh_normals = begin_export_section(file, MESHES_MESH_NORMALS);

        std::vector<Vector3> normals_stream = mesh->normals_stream();
        file << (int32_t) normals_stream.size();
        for (size_t i = 0; i < normals_stream.size(); ++i) {
            file << (DTfloat) normals_stream[i].x;
            file << (DTfloat) normals_stream[i].y;
            file << (DTfloat) normals_stream[i].z;
        }

        end_export_section(file, mesh_normals); // MESHES_MESH_NORMALS


        // MESHES_MESH_UV_SETS
        DTsize mesh_uv_sets = begin_export_section(file, MESHES_MESH_UV_SETS);

        int32_t uv_sets_size = (mesh->uv_stream0().size() > 0 ? 1:0) + (mesh->uv_stream1().size() > 0 ? 1:0);
        file << (int32_t) uv_sets_size;

        if (mesh->uv_stream0().size() > 0) {
            DTsize mesh_uvs = begin_export_section(file, MESHES_MESH_UVS);

            std::vector<Vector2> uvs_stream = mesh->uv_stream0();
            file << (int32_t) uvs_stream.size();
            for (size_t i = 0; i < uvs_stream.size(); ++i) {
                file << (DTfloat) uvs_stream[i].x;
                file << (DTfloat) uvs_stream[i].y;
            }

            end_export_section(file, mesh_uvs); // MESHES_MESH_UVS
        }

        if (mesh->uv_stream1().size() > 0) {
            DTsize mesh_uvs = begin_export_section(file, MESHES_MESH_UVS);

            std::vector<Vector2> uvs_stream = mesh->uv_stream1();
            file << (int32_t) uvs_stream.size();
            for (size_t i = 0; i < uvs_stream.size(); ++i) {
                file << (DTfloat) uvs_stream[i].x;
                file << (DTfloat) uvs_stream[i].y;
            }

            end_export_section(file, mesh_uvs); // MESHES_MESH_UVS
        }

        end_export_section(file, mesh_uv_sets); // MESHES_MESH_UV_SETS


// This is wrong!!
//        // MESHES_MESH_SKINNING
//        DTsize mesh_skinning = begin_export_section(file, MESHES_MESH_SKINNING);
//
//        std::vector<WeightsIndex> mesh_skinning_index = mesh->weights_index_stream();
//        std::vector<Vector4> mesh_skinning_weights = mesh->weights_strength_stream();
//
//        for (DTsize i = 0; i < mesh_skinning_index.size(); ++i) {
//            file << (int32_t) mesh_skinning_index[i].w[0];
//            file << (DTfloat) mesh_skinning_weights[i].x;
//            file << (int32_t) mesh_skinning_index[i].w[1];
//            file << (DTfloat) mesh_skinning_weights[i].y;
//            file << (int32_t) mesh_skinning_index[i].w[2];
//            file << (DTfloat) mesh_skinning_weights[i].z;
//            file << (int32_t) mesh_skinning_index[i].w[3];
//            file << (DTfloat) mesh_skinning_weights[i].w;
//        }
//
//        end_export_section(file, mesh_skinning); // MESHES_MESH_SKINNING


        // MESHES_MESH_INDICES
        DTsize mesh_index = begin_export_section(file, MESHES_MESH_INDICES);

        std::vector<Triangle> index_stream = mesh->index_stream();
        file << (int32_t) index_stream.size();
        for (size_t i = 0; i < index_stream.size(); ++i) {
            file << (uint16_t) index_stream[i].v[0];
            file << (uint16_t) index_stream[i].v[1];
            file << (uint16_t) index_stream[i].v[2];
        }

        end_export_section(file, mesh_index); // MESHES_MESH_INDICES

        end_export_section(file, mesh_location);
    }

    end_export_section(file, meshes_location);

    end_export_section(file, file_location);


}

//==============================================================================
//==============================================================================

} // DT3
