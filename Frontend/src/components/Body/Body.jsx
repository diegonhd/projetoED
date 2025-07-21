import React from "react";
import Balance from "../Balance/Balance.jsx";
import Operation from "../Operation/Operation.jsx";
import Statement from "../Statement/Statement.jsx"
import "./Body.css"

export default function Body() {
    return (
        <section className="body-container">
            <div className="info-container">
                <div>
                    <Balance />
                    <Operation />
                </div>
                <Statement />
            </div>
        </section>
    )
}