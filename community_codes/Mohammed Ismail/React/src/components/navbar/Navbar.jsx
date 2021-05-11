import React, { useState } from 'react';
import { ProSidebar, Menu, MenuItem, SubMenu } from 'react-pro-sidebar';
import 'react-pro-sidebar/dist/css/styles.css';

export const Navbar = () => {
    const [open, setOpen] = useState(false);
    const mystyle = {
        width: "200px",

    };
    return (
        <nav className="navbar navbar-vertical fixed-left navbar-expand-md navbar-light bg-white" id="sidenav-main">
            <div className="container-fluid">
                <button className="navbar-toggler" type="button" onClick={() => setOpen(true)} aria-controls="sidenav-main" aria-expanded="false" aria-label="Toggle navigation">
                    <span className="navbar-toggler-icon"></span>
                </button>
                <a className="navbar-brand pt-0" href="../index.html">
                    <img src="https://mohammed-ismail.co.za/offerZen/img/basil.jpg" className="navbar-brand-img" alt="..." style={mystyle} height="200px" />
                </a>
                {
                    open && <div className="full-page-loader"></div>
                }
                <div className={`collapse navbar-collapse ${(open ? 'show' : '')}`} id="sidenav-collapse-main">
                    <div className="navbar-collapse-header d-md-none">
                        <div className="row">
                            <div className="col-6 collapse-brand">
                                <a href="../index.html">
                                    <img src="https://mohammed-ismail.co.za/offerZen/img/basil.jpg" alt="blue brand" style={mystyle} height="200px" />
                                </a>
                            </div>
                            <div className="col-6 collapse-close">
                                <button type="button" className="navbar-toggler" onClick={() => setOpen(false)} aria-controls="sidenav-main" aria-expanded="false" aria-label="Toggle sidenav">
                                    <span></span>
                                    <span></span>
                                </button>
                            </div>
                        </div>
                    </div>
                    <ul className="navbar-nav">
                        <li className="nav-item active"><a className=" nav-link " href="/"> <i className="ni ni-tv-2 text-primary"></i> Dashboard</a></li>
                    </ul>
                    <hr className="my-3" />
                    <h6 className="navbar-heading text-muted">Extra</h6>
                    <ul className="navbar-nav mb-md-3">
                        <li className="nav-item"><a className="nav-link" href="https://mohammed-ismail.co.za" target='_blank'><i className="ni ni-circle-08"></i>My Personal Website</a></li>
                    </ul>
                </div>
            </div>
        </nav>
    );
}