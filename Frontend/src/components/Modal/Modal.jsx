import React, { Children, useState } from "react";
import { motion, AnimatePresence } from "framer-motion";
import "./Modal.css"

export default function Modal(props) {
    if (props.isOpen) {
        return (
            <div className="background">
                <motion.div 
                    className="modal-container"
                    initial={{ opacity: 0, transform: "translate3d(0, -20px, -5px)"}}
                    animate={{ opacity: 1, transform: "translate3d(0, 0, 0)"}}
                    exit={{ opacity: 0, transform: "translate3d(0, -20px, -5px)"}}
                    transition={{ duration: 0.3 }}
                >
                    <button className="button-close" onClick={() => props.setStade(false)}><svg width="20px" height="20px" viewBox="0 0 1024 1024" xmlns="http://www.w3.org/2000/svg" fill="#000000"><g id="SVGRepo_bgCarrier" stroke-width="0"></g><g id="SVGRepo_tracerCarrier" stroke-linecap="round" stroke-linejoin="round"></g><g id="SVGRepo_iconCarrier"><path fill="#000000" d="M195.2 195.2a64 64 0 0 1 90.496 0L512 421.504 738.304 195.2a64 64 0 0 1 90.496 90.496L602.496 512 828.8 738.304a64 64 0 0 1-90.496 90.496L512 602.496 285.696 828.8a64 64 0 0 1-90.496-90.496L421.504 512 195.2 285.696a64 64 0 0 1 0-90.496z"></path></g></svg></button>
                    <div>{props.children}</div>
                </motion.div>
            </div>
        )
    } else {
        return null
    }
}