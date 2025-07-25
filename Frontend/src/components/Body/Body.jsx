import React, { useState } from "react";
import Balance from "../Balance/Balance.jsx";
import Operation from "../Operation/Operation.jsx";
import Statement from "../Statement/Statement.jsx"
import "./Body.css"

export default function Body() {
    const [openStatement, setOpenStatement] = useState(false)

    return (
        <section className="body-container">
            <div className="info-container">
                <div>
                    <Balance statement={openStatement} setStatement={setOpenStatement}/>
                    <Operation />
                </div>
                <Statement isOpen={openStatement}/>
            </div>
        </section>
    )
}