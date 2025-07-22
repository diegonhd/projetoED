import React from "react";
import "./OperationInput.css"

export default function OperationInput(props) {
    return (
        <div className="input-container">
            <label>{props.label}</label>
            <input 
                type="text" 
                className="input" 
                required 
                placeholder={props.text} 
                value={props.value}
                style={{width: props.width}}
            />
        </div>
    )
}