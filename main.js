// Ensure this runs after the document has loaded to ensure createVectorModule is defined
document.addEventListener('DOMContentLoaded', (event) => {
  createVectorModule().then((Module) => {
      // Create JavaScript wrappers
      const vectorInitialize = Module.cwrap('vector_initialize', 'number', []);
      const vectorGetSize = Module.cwrap('vector_get_size', 'number', ['number']);
      const vectorGetCapacity = Module.cwrap('vector_get_capacity', 'number', ['number']);

      // Initialize a vector
      const vectorPtr = vectorInitialize();

      // Get size and capacity
      const size = vectorGetSize(vectorPtr);
      const capacity = vectorGetCapacity(vectorPtr);

      console.log(`Vector size: ${size}, capacity: ${capacity}`);
  });
});
