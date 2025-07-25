import React, { useState } from "react";
import "./OperationButton.css"

export default function OperationButton(props) {
    const [buttonOver, setButtonOver] = useState(false)

    return (
        <div className="btn-container">
            <button 
                className="btn" 
                style={{backgroundColor: buttonOver ? "#28c7b7ff" : "#16ad9eff"}}
                onClick={props.func}
                onMouseOver={() => setButtonOver(true)}
                onMouseOut={() => setButtonOver(false)}
            >
                {props.children}
            </button>
            <label htmlFor="">{props.text}</label>
        </div>
    )
}