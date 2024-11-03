"use client";
import Image from "next/image";
import { useState, useEffect } from "react";
import { v4 as uuidv4 } from 'uuid';
import { IoPersonAddSharp } from "react-icons/io5";
import { MdLibraryBooks } from "react-icons/md";
import { RxPencil2 } from "react-icons/rx";
export default function Home() {

  const [name, setName] = useState("")
  const [names, setNames] = useState([])
  const [age, setAge] = useState("")
  const [ages, setAges] = useState([])
  const [priority, setPriority] = useState("")
  const [priorities, setPriorities] = useState([])
  const [activeView, setActiveView] = useState("initial");
  const [flag, setflag] = useState("name")
  // const [rerender, setRerender] = useState(false);

  const handleName = (e) => {
    setName(e.target.value)
  }
  const handleAge = (e) => {
    setAge(e.target.value)
  }
  const handlePriority = (e) => {
    setPriority(e.target.value)
  }

  const handleAdd = () => {
    setNames([...names, { id: uuidv4(), name }])
    setName("")
    setAges([...ages, { id: uuidv4(), age }])
    setAge("")
    setPriorities([...priorities, { id: uuidv4(), priority }])
    setPriority("")
    // saveToLS()
  }

  const handleback = () => {
    if (confirm("Are you sure you want to go back?")) {
      setActiveView("initial")
    }
  }
  const sortbypriority = () => {
    setflag("priority");

    // Combine priorities and names into an array of objects, maintaining their relationship
    let combined = priorities.map((priorityObj, index) => ({
      priority: priorityObj.priority,
      name: names[index].name,
      id: names[index].id,
    }));

    // Sort the combined array based on priority
    combined.sort((a, b) => a.priority - b.priority);

    // Separate the sorted priorities and names back into individual arrays and update state
    setPriorities(combined.map(item => ({ id: item.id, priority: item.priority })));
    setNames(combined.map(item => ({ id: item.id, name: item.name })));
  }
  const sortbyage = () => {
    setflag("age");

    // Combine ages and names into an array of objects, maintaining their relationship
    let combined = ages.map((ageObj, index) => ({
      age: ageObj.age,
      name: names[index].name,
      id: names[index].id,
    }));

    // Sort the combined array based on age
    combined.sort((a, b) => a.age - b.age);

    // Separate the sorted ages and names back into individual arrays and update state
    setAges(combined.map(item => ({ id: item.id, age: item.age })));
    setNames(combined.map(item => ({ id: item.id, name: item.name })));
  };



  const sortbyname = () => {
    setflag("name")
  }

  // const handleDelete = (e, id) => {
  //   let newNames = names.filter(item => {
  //     return item.id !== id
  //   });
  //   setNames(newNames)

  // }
  const handleDelete = (e, id) => {
    setNames(names.filter(item => item.id !== id));
    setAges(ages.filter(item => item.id !== id));
    setPriorities(priorities.filter(item => item.id !== id));
  };


  // useEffect(() => {
  //   // This effect will run whenever 'rerender' changes
  //   // You can add any logic here that needs to happen after the state updates
  //   console.log("State updated:", names, ages, priorities);
  // }, [rerender, names, ages, priorities]); // Include all relevant state variables in the dependency array


  return (
    // <div className=" h-screen w-screen bg-gradient-to-r from-[#0d0214] to-[#1a0429]">
    <div className=" h-screen w-screen bg-gradient-to-br from-[#0f3d3e] via-[#0a9396] to-[#005f73]">
      {/* <div className="absolute bottom-[100px] left-5 h-[150px] w-[150px] bg-[#75c3d2]"></div> */}

      {/* <img className="w-full h-full absolute opacity-40 " src="https://t4.ftcdn.net/jpg/05/64/87/15/360_F_564871538_VMpn92eGyxmmlmV8kKUzVNzR3yk2BKmT.jpg" alt="" /> */}
      <div className="flex justify-center cursor-pointer ">
        <img className="h-[90px] w-[90px]  z-40  " src="https://upload.wikimedia.org/wikipedia/en/c/cc/NITK_Emblem.png" alt="" />
        <h1 className="text-5xl font-bold flex justify-center p-4 relative text-white text-shadow-lg">Swayam Seva Portal </h1>
      </div>
      <p className="text-lg italic font-bold text-white p-4 flex justify-center">Schedule hospital appointments seamlessly</p>

      {/* This div is for initial choice */}
      <div hidden={activeView !== "initial"} className="bg-[#05090f]  shadow-[#1a0429] shadow-2xl  z-10 h-[500px] w-[600px] mx-auto my-8 relative opacity-60   rounded-2xl">
        <div>
        <IoPersonAddSharp className="absolute top-5 left-[125px] text-4xl invert" />
          <p onClick={() => setActiveView("form")} className="text-2xl font-bold text-white p-4 flex justify-center cursor-pointer hover:bg-violet-700  ">New Registration</p>
          {/* <video src="wired-flat-21-avatar-hover-jumping.gif"></video> */}

        </div>
        <div > 
        <p onClick={() => setActiveView("schedule")} className="text-2xl font-bold text-white p-4 flex justify-center cursor-pointer  hover:bg-violet-700">View Schedule</p>
        <MdLibraryBooks className="absolute top-[80px] left-[125px] text-4xl invert"/>
        </div>

        

      </div>





      {/* This div is for form */}

      <div hidden={activeView !== "form"} className=" bg-[#184952] h-[560px] shadow-[#1a0429] shadow-xl w-[800px] mx-auto rounded-3xl">
        <div className="flex justify-end "><button onClick={handleback} className="fixed right-11 top-[80px] p-4 m-4 w-[80px] rounded-3xl hover:bg-violet-700 bg-violet-300 shadow-fuchsia-600 shadow-lg ">back</button></div>


        <div className="flex flex-col items-center justify-center gap-7 h-[420px] w-[740px]">
        <RxPencil2  className="text-4xl invert absolute top-[200px] "/>
          <div className="mx-8 text-3xl justify-evenly font-bold"><input placeholder="Enter Name" className="bg-violet-100 hover:bg-violet-200 rounded-xl w-[400px] h-[40px] p-5 text-xl" onChange={handleName} value={name} type="text" /></div>
          <div className="mx-8 text-3xl font-bold" ><input type="number" placeholder="Enter age" className="bg-violet-100 hover:bg-violet-200 rounded-xl w-[400px] h-[40px] p-5 text-xl" onChange={handleAge} value={age} /></div>
          <div className="mx-8 text-3xl font-bold" ><input type="number" className="bg-violet-100 hover:bg-violet-200 rounded-xl w-[400px] h-[40px] p-5 text-xl" onChange={handlePriority} value={priority} placeholder="Enter priority" /></div>
        </div>


        <div className="flex justify-center " ><button onClick={handleAdd} disabled={name.length <= 3} className="text-2xl font-bold text-white p-4 flex justify-center cursor-pointer hover:bg-violet-700 " >Submit</button></div>





      </div>


      {/* This div is for schedule */}

      <div hidden={activeView !== "schedule"} className=" w-screen ">
        <div className="flex justify-center p-4"><p className="text-6xl text-violet-950 font-bold ">Appointment List</p></div>
        <div className="">

          <div className="h-[450px] w-[990px] bg-[#184952] mx-auto ">
            {/* schedule as name */}
            <div className="names" hidden={flag !== "name"}  >
              {names.length === 0 && <div className='m-5 p-4 flex justify-center text-2xl font-bold text-slate-800 '><i>You have no appointments</i></div>}

              <ol type="1">
                {names.map((person) => (
                  <div className="flex justify-between">
                    <li key={person.id} className="mx-5 p-2 text-2xl font-bold text-white ">{person.name}</li>
                    <button onClick={(e) => { handleDelete(e, person.id) }} className="mx-5 p-2 text-lg font-bold bg-violet-300 hover:bg-violet-700 shadow-fuchsia-600 shadow-lg rounded-xl gap-2">Finish</button></div>
                ))}
              </ol>




            </div>
            {/* shedule by priority */}
            <div hidden={flag !== "priority"}>
              {names.length === 0 && <div className='m-5 p-4 flex justify-center text-2xl font-bold text-slate-800 '><i>You have no appointments</i></div>}

              <ol type="1">
                {names.map((person) => (
                  <div className="flex justify-between">
                    <li key={person.id} className="mx-5 p-2 text-2xl font-bold text-white ">{person.name}</li>
                    <button onClick={(e) => { handleDelete(e, person.id) }} className="mx-5 p-2 text-2xl font-bold bg-violet-300 hover:bg-violet-700 shadow-fuchsia-600 shadow-lg ">Finish</button></div>
                ))}
              </ol>

            </div>



            {/* shedule by age */}
            <div hidden={flag !== "age"}>
              {/* {ages.length === 0 && <div className='m-5 p-4 flex justify-center text-2xl font-bold text-slate-800 '><i>You have no appointments</i></div>}

            <ol type="1">
              {ages.map((person) => (
                <div className="flex justify-between">
                  <li key={person.id} className="mx-5 p-2 text-2xl font-bold text-slate-700 ">{person.age}</li>
                  <button className="mx-5 p-2 text-2xl font-bold text-slate-700 ">Finish</button></div>
              ))}
            </ol> */}
              {names.length === 0 && <div className='m-5 p-4 flex justify-center text-2xl text-white font-bold  '><i>You have no appointments</i></div>}

              {/* <ol type="1" style={{ listStyleType: 'decimal', marginLeft: '20px' }}>
  {names.map((person) => (
    <li key={person.id} style={{ marginBottom: '10px' }}>
      <span className="text-2xl font-bold text-slate-700">{person.name}</span>
      <button className="ml-5 text-xl font-bold text-slate-700">Finish</button>
    </li>
  ))}
</ol> */}
              <ol type="1" className="list-decimal pl-5">
                {names.map((person) => (
                  <li key={person.id} className="p-2 text-2xl font-bold text-white flex justify-between">
                    {person.name}
                    <button onClick={(e) => { handleDelete(e, person.id) }} className="ml-5 text-xl font-bold bg-violet-300 hover:bg-violet-700 shadow-fuchsia-600 shadow-lg">Finish</button>
                  </li>
                ))}
              </ol>






            </div>
          </div>


          <button onClick={sortbypriority} className=" fixed left-6 top-[100px] p-4 mx-4 w-[160px] rounded-3xl hover:bg-violet-700 shadow-fuchsia-600 shadow-lg flex justify-center bg-violet-300 ">Sort by Priority</button>
          <button onClick={sortbyage} className=" fixed left-6 top-[170px] p-4 mx-4 w-[160px] rounded-3xl hover:bg-violet-700 flex justify-center shadow-fuchsia-600 shadow-lg bg-violet-300 ">Sort by Age</button>
          <button className=" fixed left-6 top-[240px] p-4 mx-4 w-[160px] rounded-3xl hover:bg-violet-700 flex justify-center shadow-fuchsia-600 shadow-lg bg-violet-300 ">Sort by Time</button>

          <div>

          </div>

        </div>
        <div className="flex justify-end "><button onClick={handleback} className="p-4 m-4 w-[80px] rounded-3xl hover:bg-violet-700 fixed right-8 top-[80px] bg-violet-300 shadow-fuchsia-600 shadow-lg ">back</button></div>
      </div>

    </div >
  );
}




// 