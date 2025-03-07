//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Copyright (c) Lawrence Livermore National Security, LLC and other Ascent
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Ascent.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//-----------------------------------------------------------------------------
///
/// file: t_ascent_slice.cpp
///
//-----------------------------------------------------------------------------


#include "gtest/gtest.h"

#include <ascent.hpp>
#include <ascent_hola.hpp>

#include <iostream>
#include <math.h>

#include <conduit_blueprint.hpp>

#include "t_config.hpp"
#include "t_utils.hpp"


using namespace std;
using namespace conduit;
using namespace ascent;

//-----------------------------------------------------------------------------
TEST(ascent_devil_ray, test_pseudocolor_cinema)
{   Node n;
    ascent::about(n);

    //
    // Create an example mesh.
    //
    Node data, hola_opts, verify_info;
    hola_opts["root_file"] = test_data_file("taylor_green.cycle_001860.root");
    ascent::hola("relay/blueprint/mesh", hola_opts, data);
    EXPECT_TRUE(conduit::blueprint::mesh::verify(data,verify_info));

    ASCENT_INFO("Testing Devil Ray");

    std::string db_name = "pseudo_taylor";
    string output_path = "./cinema_databases/" + db_name;
    string output_file = conduit::utils::join_file_path(output_path, "info.json");
    // remove old file before rendering
    if(conduit::utils::is_file(output_file))
    {
        conduit::utils::remove_file(output_file);
    }

    //
    // Create the actions.
    //

    conduit::Node extracts;
    extracts["e1/type"] = "dray_pseudocolor";
    // filter knobs
    conduit::Node &params = extracts["e1/params/"];
    params["field"] = "density";
    params["min_value"] = 0.99;
    params["max_value"] = 1.0;
    params["log_scale"] = "false";
    params["camera/type"] = "cinema";
    params["camera/db_name"] = db_name;
    params["camera/phi"] = 5;
    params["camera/theta"] = 5;

    params["draw_mesh"] = "true";
    params["line_thickness"] = 0.1;
    float line_color[4] = {0.f, 0.f, 0.f, 1.0f};
    params["line_color"].set(line_color, 4);;

    conduit::Node actions;
    // add the extracts
    conduit::Node &add_extracts = actions.append();
    add_extracts["action"] = "add_extracts";
    add_extracts["extracts"] = extracts;

    //
    // Run Ascent
    //

    Ascent ascent;

    Node ascent_opts;
    ascent_opts["runtime/type"] = "ascent";
    ascent.open(ascent_opts);
    ascent.publish(data);
    ascent.execute(actions);
    ascent.close();

    // check that we created an image
    EXPECT_TRUE(conduit::utils::is_file(output_file));
    std::string msg = "An example of creating a cinema database "
                      "using devil ray pseudocolor plots.";
    ASCENT_ACTIONS_DUMP(actions,output_file,msg);
}

//-----------------------------------------------------------------------------
TEST(ascent_devil_ray, test_pseudocolor)
{   Node n;
    ascent::about(n);

    //
    // Create an example mesh.
    //
    Node data, hola_opts, verify_info;
    hola_opts["root_file"] = test_data_file("taylor_green.cycle_001860.root");
    ascent::hola("relay/blueprint/mesh", hola_opts, data);
    EXPECT_TRUE(conduit::blueprint::mesh::verify(data,verify_info));

    ASCENT_INFO("Testing Devil Ray");

    string output_path = prepare_output_dir();
    string output_file = conduit::utils::join_file_path(output_path,"tout_dray_surface");

    // remove old images before rendering
    remove_test_image(output_file);

    //
    // Create the actions.
    //

    conduit::Node extracts;
    extracts["e1/type"] = "dray_pseudocolor";
    // filter knobs
    conduit::Node &params = extracts["e1/params/"];
    params["field"] = "density";
    params["min_value"] = 0.99;
    params["max_value"] = 1.0;
    params["log_scale"] = "false";
    params["image_prefix"] = output_file;
    params["camera/azimuth"] = -30;
    params["camera/elevation"] = 35;

    params["draw_mesh"] = "true";
    params["line_thickness"] = 0.1;
    float line_color[4] = {0.f, 0.f, 0.f, 1.0f};
    params["line_color"].set(line_color, 4);;

    conduit::Node actions;
    // add the extracts
    conduit::Node &add_extracts = actions.append();
    add_extracts["action"] = "add_extracts";
    add_extracts["extracts"] = extracts;

    //
    // Run Ascent
    //

    Ascent ascent;

    Node ascent_opts;
    ascent_opts["runtime/type"] = "ascent";
    ascent.open(ascent_opts);
    ascent.publish(data);
    ascent.execute(actions);
    ascent.close();

    // check that we created an image
    EXPECT_TRUE(check_test_image(output_file, 0.1, "1860"));
    std::string msg = "An example of using devil ray for pseudocolor plot.";
    ASCENT_ACTIONS_DUMP(actions,output_file,msg);
}

//-----------------------------------------------------------------------------
TEST(ascent_devil_ray, test_pseudocolor_noannots)
{   Node n;
    ascent::about(n);

    //
    // Create an example mesh.
    //
    Node data, hola_opts, verify_info;
    hola_opts["root_file"] = test_data_file("taylor_green.cycle_001860.root");
    ascent::hola("relay/blueprint/mesh", hola_opts, data);
    EXPECT_TRUE(conduit::blueprint::mesh::verify(data,verify_info));

    ASCENT_INFO("Testing Devil Ray");

    string output_path = prepare_output_dir();
    string output_file = conduit::utils::join_file_path(output_path,"tout_dray_noannots");

    // remove old images before rendering
    remove_test_image(output_file);

    //
    // Create the actions.
    //

    conduit::Node extracts;
    extracts["e1/type"] = "dray_pseudocolor";

    // filter knobs
    conduit::Node &params = extracts["e1/params/"];
    params["field"] = "density";
    params["min_value"] = 0.99;
    params["max_value"] = 1.0;
    params["annotations"] = "false";
    params["log_scale"] = "false";
    params["image_prefix"] = output_file;
    params["camera/azimuth"] = -30;
    params["camera/elevation"] = 35;

    params["draw_mesh"] = "true";
    params["line_thickness"] = 0.1;
    float line_color[4] = {0.f, 0.f, 0.f, 1.0f};
    params["line_color"].set(line_color, 4);;

    conduit::Node actions;
    // add the extracts
    conduit::Node &add_extracts = actions.append();
    add_extracts["action"] = "add_extracts";
    add_extracts["extracts"] = extracts;

    //
    // Run Ascent
    //

    Ascent ascent;

    Node ascent_opts;
    ascent_opts["runtime/type"] = "ascent";
    ascent.open(ascent_opts);
    ascent.publish(data);
    ascent.execute(actions);
    ascent.close();

    // check that we created an image
    EXPECT_TRUE(check_test_image(output_file, 0.1, "1860"));
    std::string msg = "An example of using devil ray for pseudocolor plot with no annotations.";
    ASCENT_ACTIONS_DUMP(actions,output_file,msg);
}
//-----------------------------------------------------------------------------
TEST(ascent_devil_ray, test_3slice)
{
    Node n;
    ascent::about(n);

    //
    // Create an example mesh.
    //
    Node data, hola_opts, verify_info;
    hola_opts["root_file"] = test_data_file("taylor_green.cycle_001860.root");
    ascent::hola("relay/blueprint/mesh", hola_opts, data);
    EXPECT_TRUE(conduit::blueprint::mesh::verify(data,verify_info));

    ASCENT_INFO("Testing Devil Ray");

    string output_path = prepare_output_dir();
    string output_file = conduit::utils::join_file_path(output_path,"tout_dray_3slice");

    // remove old images before rendering
    remove_test_image(output_file);

    //
    // Create the actions.
    //

    conduit::Node extracts;
    extracts["e1/type"] = "dray_3slice";
    // filter knobs
    conduit::Node &params = extracts["e1/params/"];
    params["field"] = "density";
    params["min_value"] = 0.99;
    params["max_value"] = 1.0;
    params["log_scale"] = "false";
    params["image_prefix"] = output_file;
    params["camera/azimuth"] = -30;
    params["camera/elevation"] = 35;

    params["x_offset"] = 0.;
    params["y_offset"] = 0.;
    params["z_offset"] = 0.;

    conduit::Node actions;
    // add the extracts
    conduit::Node &add_extracts = actions.append();
    add_extracts["action"] = "add_extracts";
    add_extracts["extracts"] = extracts;

    //
    // Run Ascent
    //

    Ascent ascent;

    Node ascent_opts;
    ascent_opts["runtime/type"] = "ascent";
    ascent.open(ascent_opts);
    ascent.publish(data);
    ascent.execute(actions);
    ascent.close();

    // check that we created an image
    EXPECT_TRUE(check_test_image(output_file, 0.1, "1860"));
    std::string msg = "An example of using devil ray for a three sliced pseudocolor plot.";
    ASCENT_ACTIONS_DUMP(actions,output_file,msg);
}

//-----------------------------------------------------------------------------
TEST(ascent_devil_ray, test_3slice_cinema_no_sweep)
{
    Node n;
    ascent::about(n);

    //
    // Create an example mesh.
    //
    Node data, hola_opts, verify_info;
    hola_opts["root_file"] = test_data_file("taylor_green.cycle_001860.root");
    ascent::hola("relay/blueprint/mesh", hola_opts, data);
    EXPECT_TRUE(conduit::blueprint::mesh::verify(data,verify_info));

    ASCENT_INFO("Testing Devil Ray");

    std::string db_name = "pseudo_3slice";
    string output_path = "./cinema_databases/" + db_name;
    string output_file = conduit::utils::join_file_path(output_path, "info.json");
    // remove old file before rendering
    if(conduit::utils::is_file(output_file))
    {
        conduit::utils::remove_file(output_file);
    }

    //
    // Create the actions.
    //

    conduit::Node extracts;
    extracts["e1/type"] = "dray_3slice";
    // filter knobs
    conduit::Node &params = extracts["e1/params/"];
    params["field"] = "density";
    params["min_value"] = 0.99;
    params["max_value"] = 1.0;
    params["log_scale"] = "false";

    params["camera/type"] = "cinema";
    params["camera/db_name"] = db_name;
    params["camera/phi"] = 2;
    params["camera/theta"] = 2;

    params["x_offset"] = 0.7;
    params["y_offset"] = 0.2;
    params["z_offset"] = 0.4;

    conduit::Node actions;
    // add the extracts
    conduit::Node &add_extracts = actions.append();
    add_extracts["action"] = "add_extracts";
    add_extracts["extracts"] = extracts;

    //
    // Run Ascent
    //

    Ascent ascent;

    Node ascent_opts;
    ascent_opts["runtime/type"] = "ascent";
    ascent.open(ascent_opts);
    ascent.publish(data);
    ascent.execute(actions);
    ascent.close();

    // check that we created an image
    EXPECT_TRUE(conduit::utils::is_file(output_file));
    std::string msg = "An example of creating a cinema database using devil "
                      " ray for a 3 slice plot.";
    ASCENT_ACTIONS_DUMP(actions,output_file,msg);
}

TEST(ascent_devil_ray, test_3slice_cinema_sweep)
{
    Node n;
    ascent::about(n);

    //
    // Create an example mesh.
    //
    Node data, hola_opts, verify_info;
    hola_opts["root_file"] = test_data_file("taylor_green.cycle_001860.root");
    ascent::hola("relay/blueprint/mesh", hola_opts, data);
    EXPECT_TRUE(conduit::blueprint::mesh::verify(data,verify_info));

    ASCENT_INFO("Testing Devil Ray");

    std::string db_name = "pseudo_3slice_sweep";
    string output_path = "./cinema_databases/" + db_name;
    string output_file = conduit::utils::join_file_path(output_path, "info.json");
    // remove old file before rendering
    if(conduit::utils::is_file(output_file))
    {
        conduit::utils::remove_file(output_file);
    }

    //
    // Create the actions.
    //

    conduit::Node extracts;
    extracts["e1/type"] = "dray_3slice";
    // filter knobs
    conduit::Node &params = extracts["e1/params/"];
    params["field"] = "density";
    params["min_value"] = 0.99;
    params["max_value"] = 1.0;
    params["log_scale"] = "false";

    params["camera/type"] = "cinema";
    params["camera/db_name"] = db_name;
    params["camera/phi"] = 2;
    params["camera/theta"] = 2;

    params["sweep/count"] = 2;
    params["sweep/axis"] = "x";
    params["x_offset"] = 0.7;
    params["y_offset"] = 0.2;
    params["z_offset"] = 0.4;

    conduit::Node actions;
    // add the extracts
    conduit::Node &add_extracts = actions.append();
    add_extracts["action"] = "add_extracts";
    add_extracts["extracts"] = extracts;

    //
    // Run Ascent
    //

    Ascent ascent;

    Node ascent_opts;
    ascent_opts["runtime/type"] = "ascent";
    ascent.open(ascent_opts);
    ascent.publish(data);
    ascent.execute(actions);
    ascent.close();

    // check that we created an image
    EXPECT_TRUE(conduit::utils::is_file(output_file));
    std::string msg = "An example of creating a cinema database using devil "
                      " ray for a 3 slice plot.";
    ASCENT_ACTIONS_DUMP(actions,output_file,msg);
}

//-----------------------------------------------------------------------------
TEST(ascent_devil_ray, test_volume)
{
    Node n;
    ascent::about(n);

    //
    // Create an example mesh.
    //
    Node data, hola_opts, verify_info;
    hola_opts["root_file"] = test_data_file("taylor_green.cycle_001860.root");
    ascent::hola("relay/blueprint/mesh", hola_opts, data);
    EXPECT_TRUE(conduit::blueprint::mesh::verify(data,verify_info));

    ASCENT_INFO("Testing Devil Ray");

    string output_path = prepare_output_dir();
    string output_file = conduit::utils::join_file_path(output_path,"tout_dray_volume");

    // remove old images before rendering
    remove_test_image(output_file);

    //
    // Create the actions.
    //

    conduit::Node extracts;
    extracts["e1/type"] = "dray_volume";
    // filter knobs
    conduit::Node &params = extracts["e1/params/"];
    params["field"] = "density";
    //params["min_value"] = 0.955;
    params["min_value"] = 0.98;
    params["max_value"] = 1.04;
    params["log_scale"] = "false";
    params["image_prefix"] = output_file;
    params["camera/azimuth"] = -30;
    params["camera/elevation"] = 35;

    params["samples"] = 100;

    conduit::Node actions;
    // add the extracts
    conduit::Node &add_extracts = actions.append();
    add_extracts["action"] = "add_extracts";
    add_extracts["extracts"] = extracts;

    //
    // Run Ascent
    //

    Ascent ascent;

    Node ascent_opts;
    ascent_opts["runtime/type"] = "ascent";
    ascent.open(ascent_opts);
    ascent.publish(data);
    ascent.execute(actions);
    ascent.close();

    // check that we created an image
    EXPECT_TRUE(check_test_image(output_file, 0.1, "1860"));
    std::string msg = "An example of using devil ray for pseudocolor plot.";
    ASCENT_ACTIONS_DUMP(actions,output_file,msg);
}
//-----------------------------------------------------------------------------
TEST(ascent_devil_ray, test_reflect)
{
    Node n;
    ascent::about(n);

    //
    // Create an example mesh.
    //
    Node data, hola_opts, verify_info;
    hola_opts["root_file"] = test_data_file("taylor_green.cycle_001860.root");
    ascent::hola("relay/blueprint/mesh", hola_opts, data);
    EXPECT_TRUE(conduit::blueprint::mesh::verify(data,verify_info));

    ASCENT_INFO("Testing Devil Ray");

    string output_path = prepare_output_dir();
    string output_file = conduit::utils::join_file_path(output_path,"tout_reflect");

    // remove old images before rendering
    remove_test_image(output_file);

    //
    // Create the actions.
    //

    conduit::Node pipelines;
    pipelines["p1/f1/type"] = "dray_reflect";
    // filter knobs
    conduit::Node &rparams = pipelines["p1/f1/params/"];
    rparams["point/x"] = 0.;
    rparams["point/y"] = 0.;
    rparams["point/z"] = 0.;
    rparams["normal/x"] = 0.;
    rparams["normal/y"] = 1.;
    rparams["normal/z"] = 0.;

    conduit::Node extracts;
    extracts["e1/type"] = "dray_pseudocolor";
    extracts["e1/pipeline"] = "p1";
    // filter knobs
    conduit::Node &params = extracts["e1/params/"];
    params["field"] = "density";
    //params["min_value"] = 0.955;
    params["min_value"] = 0.98;
    params["max_value"] = 1.04;
    params["log_scale"] = "false";
    params["image_prefix"] = output_file;
    params["camera/azimuth"] = -30;
    params["camera/elevation"] = 35;

    conduit::Node actions;
    // add the pipeline
    conduit::Node &add_pipelines = actions.append();
    add_pipelines["action"] = "add_pipelines";
    add_pipelines["pipelines"] = pipelines;
    // add the extracts
    conduit::Node &add_extracts = actions.append();
    add_extracts["action"] = "add_extracts";
    add_extracts["extracts"] = extracts;

    //
    // Run Ascent
    //

    Ascent ascent;

    Node ascent_opts;
    ascent_opts["runtime/type"] = "ascent";
    ascent.open(ascent_opts);
    ascent.publish(data);
    ascent.execute(actions);
    ascent.close();

    // check that we created an image
    EXPECT_TRUE(check_test_image(output_file, 0.1, "1860"));
    std::string msg = "An example of using devil ray to reflect a data set.";
    ASCENT_ACTIONS_DUMP(actions,output_file,msg);
}

//-----------------------------------------------------------------------------
TEST(ascent_devil_ray, test_scalar_rendering)
{
    Node n;
    ascent::about(n);

    //
    // Create an example mesh.
    //
    Node data, hola_opts, verify_info;
    hola_opts["root_file"] = test_data_file("taylor_green.cycle_001860.root");
    ascent::hola("relay/blueprint/mesh", hola_opts, data);
    EXPECT_TRUE(conduit::blueprint::mesh::verify(data,verify_info));

    ASCENT_INFO("Testing Devil Ray");

    string output_path = prepare_output_dir();
    string output_file = conduit::utils::join_file_path(output_path,"tout_scalar_renderer");

    //
    // Create the actions.
    //

    conduit::Node pipelines;
    // pipeline 1
    pipelines["pl1/f1/type"] = "dray_project_2d";
    // filter knobs
    conduit::Node &params = pipelines["pl1/f1/params"];
    params["image_width"] = 512;
    params["image_height"] = 512;
    params["fields"].append() = "density";

    conduit::Node extracts;
    extracts["e1/type"]  = "relay";
    extracts["e1/pipeline"] = "pl1";

    extracts["e1/params/path"] = output_file;
    extracts["e1/params/protocol"] = "blueprint/mesh/hdf5";

    conduit::Node actions;
    // add the extracts
    conduit::Node &add_extracts = actions.append();
    add_extracts["action"] = "add_extracts";
    add_extracts["extracts"] = extracts;
    // add the pipeline
    conduit::Node &add_pipelines= actions.append();
    add_pipelines["action"] = "add_pipelines";
    add_pipelines["pipelines"] = pipelines;

    //
    // Run Ascent
    //
    Ascent ascent;

    Node ascent_opts;
    ascent_opts["runtime/type"] = "ascent";
    ascent.open(ascent_opts);
    ascent.publish(data);
    ascent.execute(actions);
    ascent.close();

    // check that we created an image
    std::string msg = "An example of using devil ray scalar rendering.";
    ASCENT_ACTIONS_DUMP(actions,output_file,msg);
}


//-----------------------------------------------------------------------------
TEST(ascent_devil_ray, test_scalar_rendering_lo)
{
    Node n;
    ascent::about(n);

    //
    // Create an example mesh.
    //
    Node data, verify_info;
    conduit::blueprint::mesh::examples::braid("hexs",
                                              10,
                                              10,
                                              10,
                                              data);

    EXPECT_TRUE(conduit::blueprint::mesh::verify(data,verify_info));

    ASCENT_INFO("Testing Devil Ray Scalar Renderer (Low Order)");

    string output_path = prepare_output_dir();
    string output_file = conduit::utils::join_file_path(output_path,"tout_scalar_renderer_lo");

    //
    // Create the actions.
    //

    conduit::Node actions;
    // add the pipeline
    conduit::Node &add_pipelines= actions.append();
    add_pipelines["action"] = "add_pipelines";
    conduit::Node &pipelines = add_pipelines["pipelines"];

    // pipeline 1
    pipelines["pl1/f1/type"] = "dray_project_2d";
    // filter knobs
    conduit::Node &params = pipelines["pl1/f1/params"];
    params["image_width"] = 512;
    params["image_height"] = 512;
    params["fields"].append() = "braid";

    // add the extracts

    // hdf5 output
    conduit::Node &add_extracts = actions.append();
    add_extracts["action"] = "add_extracts";
    conduit::Node &extracts = add_extracts["extracts"];

    extracts["e1/type"]  = "relay";
    extracts["e1/pipeline"] = "pl1";

    extracts["e1/params/path"] = output_file;
    extracts["e1/params/protocol"] = "blueprint/mesh/hdf5";

    // in-memory output
    extracts["e2/type"]  = "conduit";
    extracts["e2/pipeline"] = "pl1";

    std::cout << "Actions:" << std::endl << actions.to_yaml();

    //
    // Run Ascent
    //
    Ascent ascent;
    ascent.open();
    ascent.publish(data);
    ascent.execute(actions);
    
    conduit::Node &info = ascent.info();
    info["extracts"][1].print();

    ascent.close();

    // check that we created an image
    std::string msg = "An example of using devil ray scalar rendering on a low order dataset.";
    ASCENT_ACTIONS_DUMP(actions,output_file,msg);
}

//-----------------------------------------------------------------------------
TEST(ascent_devil_ray, test_scalar_rendering_plane)
{
    Node n;
    ascent::about(n);

    //
    // Create an example mesh.
    //
    Node data, hola_opts, verify_info;
    hola_opts["root_file"] = test_data_file("taylor_green.cycle_001860.root");
    ascent::hola("relay/blueprint/mesh", hola_opts, data);
    EXPECT_TRUE(conduit::blueprint::mesh::verify(data,verify_info));

    ASCENT_INFO("Testing Devil Ray");

    string output_path = prepare_output_dir();
    string output_file
      = conduit::utils::join_file_path(output_path,"tout_scalar_renderer_plane");

    //
    // Create the actions.
    //

    conduit::Node pipelines;
    // pipeline 1
    pipelines["pl1/f1/type"] = "dray_project_2d";
    // filter knobs
    conduit::Node &params = pipelines["pl1/f1/params"];
    params["image_width"] = 512;
    params["image_height"] = 512;

    double center[3] = {0.5, 0.0, -1.5};
    double up[3] = {0., 1., 0.};
    double normal[3] = {0., 0.25, 1.};
    params["plane/center"].set(center,3);
    params["plane/up"].set(up,3);
    params["plane/normal"].set(normal,3);
    params["plane/width"] = 1.5f;
    params["plane/height"] = 1.5f;

    params["fields"].append() = "density";

    conduit::Node extracts;
    extracts["e1/type"]  = "relay";
    extracts["e1/pipeline"] = "pl1";

    extracts["e1/params/path"] = output_file;
    extracts["e1/params/protocol"] = "blueprint/mesh/hdf5";

    conduit::Node actions;
    // add the extracts
    conduit::Node &add_extracts = actions.append();
    add_extracts["action"] = "add_extracts";
    add_extracts["extracts"] = extracts;
    // add the pipeline
    conduit::Node &add_pipelines= actions.append();
    add_pipelines["action"] = "add_pipelines";
    add_pipelines["pipelines"] = pipelines;

    //
    // Run Ascent
    //
    Ascent ascent;

    Node ascent_opts;
    ascent_opts["runtime/type"] = "ascent";
    ascent.open(ascent_opts);
    ascent.publish(data);
    ascent.execute(actions);
    ascent.close();

    // check that we created an image
    std::string msg = "An example of using devil ray scalar rendering using a plane.";
    ASCENT_ACTIONS_DUMP(actions,output_file,msg);
}

//-----------------------------------------------------------------------------
TEST(ascent_devil_ray, test_vector_component)
{
    Node n;
    ascent::about(n);

    //
    // Create an example mesh.
    //
    Node data, hola_opts, verify_info;
    hola_opts["root_file"] = test_data_file("taylor_green.cycle_001860.root");
    ascent::hola("relay/blueprint/mesh", hola_opts, data);
    EXPECT_TRUE(conduit::blueprint::mesh::verify(data,verify_info));

    ASCENT_INFO("Testing Devil Ray");

    string output_path = prepare_output_dir();
    string output_file = conduit::utils::join_file_path(output_path,"tout_vector_comp");

    // remove old images before rendering
    remove_test_image(output_file);

    //
    // Create the actions.
    //

    conduit::Node pipelines;
    pipelines["p1/f1/type"] = "dray_vector_component";
    // filter knobs
    conduit::Node &rparams = pipelines["p1/f1/params/"];
    rparams["field"] = "velocity";
    rparams["output_name"] = "velocity_x";
    rparams["component"] = 0;

    conduit::Node extracts;
    extracts["e1/type"] = "dray_pseudocolor";
    extracts["e1/pipeline"] = "p1";
    // filter knobs
    conduit::Node &params = extracts["e1/params/"];
    params["field"] = "velocity_x";
    //params["min_value"] = 0.955;
    params["log_scale"] = "false";
    params["image_prefix"] = output_file;
    params["camera/azimuth"] = -30;
    params["camera/elevation"] = 35;

    conduit::Node actions;
    // add the pipeline
    conduit::Node &add_pipelines = actions.append();
    add_pipelines["action"] = "add_pipelines";
    add_pipelines["pipelines"] = pipelines;
    // add the extracts
    conduit::Node &add_extracts = actions.append();
    add_extracts["action"] = "add_extracts";
    add_extracts["extracts"] = extracts;

    //
    // Run Ascent
    //

    Ascent ascent;

    Node ascent_opts;
    ascent_opts["runtime/type"] = "ascent";
    ascent.open(ascent_opts);
    ascent.publish(data);
    ascent.execute(actions);
    ascent.close();

    // check that we created an image
    EXPECT_TRUE(check_test_image(output_file, 0.1, "1860"));
    std::string msg = "An example of using devil ray extract a component of a vector.";
    ASCENT_ACTIONS_DUMP(actions,output_file,msg);
}

//-----------------------------------------------------------------------------
TEST(ascent_devil_ray, test_dray_compressed_color_table)
{
    // the ascent runtime is currently our only rendering runtime
    Node n;
    ascent::about(n);

    //
    // Create an example mesh.
    //
    Node data, verify_info;
    conduit::blueprint::mesh::examples::braid("hexs",
                                              10,
                                              10,
                                              10,
                                              data);

    EXPECT_TRUE(conduit::blueprint::mesh::verify(data,verify_info));


    ASCENT_INFO("Testing Devil Ray Compressed Color Table");

    string output_path = prepare_output_dir();
    string output_file = conduit::utils::join_file_path(output_path,"dray_compressed_color_table");

    // remove old images before rendering
    remove_test_image(output_file);

    //
    // Create the actions.
    //

    conduit::Node control_points;
    control_points["r"] = {.23, .48, .99};
    control_points["g"] = {0.08, .23, 1.};
    control_points["b"] = {0.08, .04, .96};
    control_points["a"] = {1., 1., 1.};
    control_points["position"] = {0., .5, 1.};    

    conduit::Node extracts;
    extracts["e1/type"]  = "dray_pseudocolor";
    extracts["e1/params/field"] = "braid";
    extracts["e1/params/color_table/control_points"] = control_points;
    extracts["e1/params/image_width"]  = 512;
    extracts["e1/params/image_height"] = 512;
    extracts["e1/params/image_prefix"]   = output_file;

    conduit::Node actions;
    conduit::Node &add_plots = actions.append();
    add_plots["action"] = "add_extracts";
    add_plots["extracts"] = extracts;

    //
    // Run Ascent
    //

    Ascent ascent;

    Node ascent_opts;
    ascent_opts["runtime/type"] = "ascent";
    ascent.open(ascent_opts);
    ascent.publish(data);
    ascent.execute(actions);
    ascent.close();

    // check that we created an image
    // EXPECT_TRUE(check_test_image(output_file));
    // std::string msg = "An example of creating a custom compressed color map.";
    // ASCENT_ACTIONS_DUMP(actions,output_file,msg);
}

//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    int result = 0;

    ::testing::InitGoogleTest(&argc, argv);

    // allow override of the data size via the command line
    result = RUN_ALL_TESTS();
    return result;
}


