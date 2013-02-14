/**
 * @file project.cpp
 * @brief Geometry project
 *
 * @author H. Q. Bovik (hqbovik)
 * @bug Unimplemented
 */

#include "project.hpp"
#include "application/opengl.hpp"

/*
   A namespace declaration. All project files use this namespace.
   Add this declaration (and its closing) to all source/headers you create.
   Note that all #includes should be BEFORE the namespace declaration.
 */
namespace _462 {

// definitions of functions for the GeometryProject class

// constructor, invoked when object is allocated
GeometryProject::GeometryProject() { }

// destructor, invoked when object is de-allocated
GeometryProject::~GeometryProject() { }

/**
 * Initialize the project, doing any necessary opengl initialization.
 * @param camera An already-initialized camera.
 * @param mesh The mesh to be rendered and subdivided.
 * @param texture_filename The filename of the texture to use with the mesh.
 *  Is null if there is no texture data with the mesh or no texture filename
 *  was passed in the arguments, in which case textures should not be used.
 * @return true on success, false on error.
 */
bool GeometryProject::initialize( const Camera* camera, const MeshData* mesh, const char* texture_filename )
{
    this->mesh = *mesh;

    // TODO opengl initialization code

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(camera->get_fov_degrees(),camera->get_aspect_ratio(),camera->get_near_clip(), camera->get_far_clip());
	
	glMatrixMode(GL_MODELVIEW);

	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat light_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
    GLfloat light_specular[] = { 0.6, 0.6, 0.6, 1.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 };

	glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
   
   	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);

	std::cout<<sizeof(double);

    return true;
}

/**
 * Clean up the project. Free any memory, etc.
 */
void GeometryProject::destroy()
{
  // TODO any cleanup code
}

/**
 * Clear the screen, then render the mesh using the given camera.
 * @param camera The logical camera to use.
 * @see scene/camera.hpp
 */
void GeometryProject::render( const Camera* camera )
{
  // TODO render code

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Vector3 pos = camera->get_position();
	Vector3 dir = camera->get_direction()+ camera->get_position();
	Vector3 up = camera->get_up();

	gluLookAt(pos.x, pos.y, pos.z, 
			  dir.x,dir.y,dir.z,
			  up.x, up.y, up.z);

	glEnableClientState( GL_VERTEX_ARRAY ); 
	glVertexPointer( 3, GL_DOUBLE, 8*sizeof(double), mesh.vertices); 
	glColor3f(1,0,0);
		
	glDrawElements( GL_TRIANGLES, mesh.num_triangles*3, GL_UNSIGNED_INT, mesh.triangles); 
	glDisableClientState( GL_VERTEX_ARRAY ); 

	//glBegin(GL_TRIANGLES) ;
	//for(int i=0; i<mesh.num_vertices; i++)
	//{
	//	glVertex3d(mesh.vertices[i].position.x, mesh.vertices[i].position.y, mesh.vertices[i].position.z);
	//}
	//glEnd();
}


/**
 * Subdivide the mesh that we are rendering using Loop subdivison.
 */
void GeometryProject::subdivide()
{
    // TODO perform a single subdivision.
}



} /* _462 */

