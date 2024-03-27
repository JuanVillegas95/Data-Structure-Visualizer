class app {
  constructor() {
    this.container = document.createElement("div");
    this.currentView = undefined;
    document.body.appendChild(this.container);
    this.dataStructuresModule = {}; 
    this.vectorPtr = undefined;
    this.initializeDataStructuresModule();
  }

  initializeDataStructuresModule() {
    if (typeof dataStructuresModule !== 'undefined') {
      dataStructuresModule().then((Module) => {
        this.dataStructuresModule = {
          vectorInitialize: Module.cwrap('vector_initialize', 'number', []),
          vectorGetSize: Module.cwrap('vector_get_size', 'number', ['number']),
          vectorGetCapacity: Module.cwrap('vector_get_capacity', 'number', ['number']),
          vectorDestroy: Module.cwrap('vector_destroy', null, ['number']),
          vectorPush: Module.cwrap('vector_push', null, ['number', 'number']),
          vectorPop: Module.cwrap('vector_pop', 'number', ['number']),
          vectorGet: Module.cwrap('vector_get', 'number', ['number', 'number']),
          vectorSet: Module.cwrap('vector_set', null, ['number', 'number', 'number']),
          vectorMax: Module.cwrap('vector_max', 'number', ['number']),
          vectorMin: Module.cwrap('vector_min', 'number', ['number']),
          vectorSum: Module.cwrap('vector_sum', 'number', ['number']),
          vectorAvg: Module.cwrap('vector_avg', 'number', ['number']),
          vectorInsert: Module.cwrap('vector_insert', null, ['number', 'number', 'number']),
          vectorDelete: Module.cwrap('vector_delete', null, ['number', 'number']),
          vectorReverse: Module.cwrap('vector_reverse', null, ['number']),
          vectorLeftShift: Module.cwrap('vector_left_shift', null, ['number']),
          vectorConcat: Module.cwrap('vector_concat', null, ['number', 'number']),
          vectorCompare: Module.cwrap('vector_compare', 'number', ['number', 'number']),
          vectorCopy: Module.cwrap('vector_copy', null, ['number', 'number']),
          vectorIsSorted: Module.cwrap('vector_is_sorted', 'number', ['number']),
          vectorBinarySearch: Module.cwrap('vector_binary_search', 'number', ['number', 'number']),
          // Add other function wrappers as you expand your module to include more data structures
        };
        console.log("Data structures module and function wrappers are ready.");
      }).catch(error => console.error("Failed to initialize the data structures module:", error));
    } else {
      console.error("dataStructuresModule is not defined. Ensure the script is loaded correctly.");
    }
  }

  handleVectorOperation(label, onComplete) {
    if (!this.dataStructuresModule) {
        console.error("Data structures module not loaded.");
        return;
    }
    let result;
    switch (label) {
        case "Initialize":
            this.vectorPtr = this.dataStructuresModule.vectorInitialize();
            console.log("Vector initialized.");
            break;
        case "Get Size":
            result = this.dataStructuresModule.vectorGetSize(this.vectorPtr);
            console.log(`Vector size: ${result}`);
            break;
        case "Get Capacity":
            result = this.dataStructuresModule.vectorGetCapacity(this.vectorPtr);
            console.log(`Vector capacity: ${result}`);
            break;
        case "Destroy":
            this.dataStructuresModule.vectorDestroy(this.vectorPtr);
            console.log("Vector destroyed.");
            break;
        case "Push":
            // Assuming you have a value to push. This needs to be adjusted based on your UI/input mechanism.
            const valueToPush = 10; // Example value
            this.dataStructuresModule.vectorPush(this.vectorPtr, valueToPush);
            console.log(`Pushed ${valueToPush} to vector.`);
            break;
        case "Pop":
            result = this.dataStructuresModule.vectorPop(this.vectorPtr);
            console.log(`Popped value: ${result}`);
            break;
        case "Get":
            // Assuming you want to get a value at a specific index. This index should come from your UI/input.
            const getIndex = 0; // Example index
            result = this.dataStructuresModule.vectorGet(this.vectorPtr, getIndex);
            console.log(`Value at index ${getIndex}: ${result}`);
            break;
        case "Set":
            // Assuming you want to set a value at a specific index.
            const setIndex = 0; // Example index
            const setValue = 20; // Example value to set
            this.dataStructuresModule.vectorSet(this.vectorPtr, setIndex, setValue);
            console.log(`Set value ${setValue} at index ${setIndex}`);
            break;
        case "Max":
            result = this.dataStructuresModule.vectorMax(this.vectorPtr);
            console.log(`Maximum value in vector: ${result}`);
            break;
        case "Min":
            result = this.dataStructuresModule.vectorMin(this.vectorPtr);
            console.log(`Minimum value in vector: ${result}`);
            break;
        case "Sum":
            result = this.dataStructuresModule.vectorSum(this.vectorPtr);
            console.log(`Sum of vector values: ${result}`);
            break;
        case "Avg":
            result = this.dataStructuresModule.vectorAvg(this.vectorPtr);
            console.log(`Average of vector values: ${result}`);
            break;
        case "Insert":
            // Assuming you have a value and index for insertion.
            const insertIndex = 1; // Example index
            const insertValue = 30; // Example value
            this.dataStructuresModule.vectorInsert(this.vectorPtr, insertIndex, insertValue);
            console.log(`Inserted ${insertValue} at index ${insertIndex}`);
            break;
        case "Delete":
            // Assuming you want to delete a value at a specific index.
            const deleteIndex = 1; // Example index
            this.dataStructuresModule.vectorDelete(this.vectorPtr, deleteIndex);
            console.log(`Deleted value at index ${deleteIndex}`);
            break;
        case "Reverse":
            this.dataStructuresModule.vectorReverse(this.vectorPtr);
            console.log("Vector reversed.");
            break;
        case "Left Shift":
            this.dataStructuresModule.vectorLeftShift(this.vectorPtr);
            console.log("Vector left-shifted.");
            break;
        // Continue adding cases as necessary for other operations
        default:
            console.error(`Operation "${label}" not recognized.`);
            break;
    }
    onComplete(label);
}


  updateView(HTMLElement) {
    if(this.currentView){
      this.container.removeChild(this.currentView);
    }
    this.currentView = HTMLElement;
    this.container.appendChild(HTMLElement);
  }

  createView({ className = "", id = "", innerHTML = "", css = "" }) {
    const view = document.createElement("div");
    view.className = className;
    view.id = id;
    view.innerHTML = innerHTML;
    view.style.cssText = css;
    return view;
  }

  createButtonContainer({ labels = [], containerCss = "", onComplete = () => {} }) {
    const buttonContainer = document.createElement("div");
    buttonContainer.style.cssText = containerCss;

    let buttonDuration = 1000;
    labels.forEach((label) => {
      const button = document.createElement("button");
      button.innerHTML = label;
      button.className = "buttons";
      button.id = label;
      // Ensure anime.js is included in your project
      anime({
        targets: button,
        scale: [{ value: 2, duration: buttonDuration }],
      });
      buttonDuration += 200;

      button.addEventListener("click", () => {
        const buttons = document.querySelectorAll(".buttons");
        anime({
          targets: buttons,
          opacity: 0,
          scale: 0.5,
          duration: buttonDuration,
          easing: "easeInOutExpo",
          complete: () => onComplete(label),
        });
      });
      buttonContainer.appendChild(button);
    });
    return buttonContainer;
  }
}

function createVectorView(dataStructuresVisualizer){
  const vectorView = dataStructuresVisualizer.createView({
    className: "vectorView",
    innerHTML: "Vector view content",
    id: "vectorView",
    css: `
    display: flex;
    flex-direction: row;
    justify-content: center;
    align-items: center;
    height: 800px;
    width: 1000px;
    background-color: black;
    border-radius: 15px;
    `,
  });
  const vectorViewButtonContainer = dataStructuresVisualizer.createButtonContainer({
    labels: ["Initialize", "Get Size", "Get Capacity", "Destroy", "More Capacity", "Push", "Display", "Pop", "Get", "Set", "Max", "Min", "Sum", "Avg", "Insert", "Delete", "Reverse", "Left Shift", "Concat", "Compare", "Copy", "Is Sorted", "Binary Search"],
    containerCss: `
      display: flex;
      flex-direction: row;
      justify-content: center;
      align-items: center;
      height: 100vh;
      width: 400px;
      gap: 30px;
    `,
  })
  vectorView.appendChild(vectorViewButtonContainer);
  return vectorView;
}

function createStringView(dataStructuresVisualizer){
  const stringView = dataStructuresVisualizer.createView({
    className: "vectorView",
    innerHTML: "Vector view content",
    id: "vectorView",
    css: `
    display: flex;
    flex-direction: row;
    justify-content: center;
    align-items: center;
    height: 800px;
    width: 1000px;
    background-color: black;
    border-radius: 15px;
    `,
  });
  return stringView;
}

function createHomeView(dataStructuresVisualizer, views){
  const homeView = dataStructuresVisualizer.createView({
    css: `
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100vh; 
    `,
  });
  const homeViewButtonContainer = dataStructuresVisualizer.createButtonContainer({
    labels: ["Vector", "String", "Linked List"],
    containerCss: `  
      display: flex;
      flex-direction: column;
      justify-content: center;
      align-items: center;
      height: 100vh;
      width: 400px;
      gap: 30px;
    `,
    onComplete: (label) => {
      if (label === "Vector") dataStructuresVisualizer.updateView(views.vectorView);
      // You can add more conditions here for "String" and "Linked List" if needed.
    },
  });
  homeView.appendChild(homeViewButtonContainer);
  return homeView;
}

function main() {
  const dataStructuresVisualizer = new app();

  const vectorView = createVectorView(dataStructuresVisualizer);
  const stringView = createStringView(dataStructuresVisualizer)

  const views = {
    vectorView: vectorView,
    stringView: stringView,
  }

  const homeView = createHomeView(dataStructuresVisualizer,views);
  dataStructuresVisualizer.updateView(homeView);
}

document.addEventListener('DOMContentLoaded', main);
