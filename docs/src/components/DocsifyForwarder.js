import React, { useEffect } from 'react';
import { useHistory } from 'react-router-dom';

function removeHashSlash(url) {
  return url.replace(/\/#\//, '/');
}

export default function DocsifyForwarder(props) {
    const history = useHistory();
    const currentUrl = window.location.href;
    if (currentUrl.includes('/#/')) {
      const newUrl = removeHashSlash(currentUrl);
      window.history.replaceState({}, '', newUrl);
      const relativePath = new URL(newUrl).pathname;
      history.push(relativePath);
    }
    return "";
}