#include <SZAS/Graphics/VertexBuffer.h>

szas::VertexBuffer::VertexBuffer(const VertexBufferDescriptor& vertexBufferDescriptor, const GraphicsResourceDescriptor& graphicsResourceDescriptor):
	GraphicsResource(graphicsResourceDescriptor), 
	m_vertexSize(vertexBufferDescriptor.vertexSize),
	m_vertexListSize(vertexBufferDescriptor.vertexListSize)
{
	//Argument Validation. Make sure they are non-null
	if (!vertexBufferDescriptor.vertexList) SZASLogThrowInvalidArgument("No vertex list provided.");
	if (!vertexBufferDescriptor.vertexListSize) SZASLogThrowInvalidArgument("Vertex list size must be non-zero");
	if (!vertexBufferDescriptor.vertexSize) SZASLogThrowInvalidArgument("Vertex size must be non-zero");

	D3D11_BUFFER_DESC bufferDescriptor{};
	//Defines size of buffer in bytes. Must be greater than 0
	//Compute the size of vertex buffer by multiplying the number of vertices by size in bites of a single vertex
	//Gives us total size in bytes of entire list
	bufferDescriptor.ByteWidth = vertexBufferDescriptor.vertexListSize * vertexBufferDescriptor.vertexSize;
	//Bind Flags. What the buffer should be used for. Since we're storing vertices it's a vertex buffer
	bufferDescriptor.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	//Define Subresource Data
	D3D11_SUBRESOURCE_DATA initialData{};
	initialData.pSysMem = vertexBufferDescriptor.vertexList; //Custom void pointer to initial dta

	//Create Buffer allocates a buffer in GPU memory, whether its vertex buffer, index buffer, or constant buffer
	SZASGraphicsLogThrowOnFail(
	m_d3dDevice.CreateBuffer
	(
		&bufferDescriptor,	//Pointer to a buffer descriptor. A structure that describes how the GPU buffer should be created
		&initialData,		//D3D11 Subresource data. Provides a way to supply initial CPU side data to the GPU resource during creation 
		&m_buffer			//Output parameter. Hold the final buffer object
	), "CreateBuffer() failed.");

}

szas::ui32 szas::VertexBuffer::GetVertexListSize() const noexcept
{
	return m_vertexListSize;
}
