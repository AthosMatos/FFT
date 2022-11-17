require('./main').onRuntimeInitialized = _ => {
    const MainCpp = require('./main').cwrap('main');
    MainCpp();
   };